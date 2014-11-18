#include "window_base.h"

#include "control_factory.h"

namespace win {

WindowBase::WindowBase(HWND hWnd) :
	mHWnd( hWnd ) {
}

WindowBase::~WindowBase() {
	::DestroyWindow (mHWnd);
}

std::string WindowBase::getText() {
	std::size_t len = ::GetWindowTextLength(mHWnd) + 1;
    std::vector<char> buffer( len );
    ::GetWindowText (mHWnd, buffer.data(), len);
    return std::string( buffer.begin(), buffer.end() );	
}

void WindowBase::setText(std::string& value) {
	::SetWindowText (mHWnd, value.c_str());
}

bool WindowBase::isVisible() {
	return ::IsWindowVisible (mHWnd);
}

void WindowBase::setVisible(bool value) {
	if (value) {
		::ShowWindow (mHWnd, SW_SHOWNOACTIVATE);
	} else {
		::ShowWindow (mHWnd, SW_HIDE);
	}
}

bool WindowBase::isEnabled() {
	return ::IsWindowEnabled (mHWnd);
}

void WindowBase::setEnabled(bool value) {
	::EnableWindow (mHWnd, value);
}

bool WindowBase::hasBorder() {
	return getExStyleBit (WS_EX_CLIENTEDGE);
}

void WindowBase::setBorder(bool value) {
	setExStyleBit (WS_EX_CLIENTEDGE, value);
	
	// Invalidate style cache
	::SetWindowPos (mHWnd, NULL, 0, 0, 0, 0, 
		SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

std::shared_ptr<FontResource> WindowBase::getFontResource() {
	return std::dynamic_pointer_cast<FontResource>(mResources[mCurrentFontResourceInstId]);
}

void WindowBase::setFontResource(std::shared_ptr<FontResource> fontResource) {
	::SendMessage (mHWnd, WM_SETFONT, reinterpret_cast<WPARAM>(fontResource->getHFont()), TRUE);

	if (!resourceExist (fontResource->getFont().get())) {
		mCurrentFontResourceInstId = fontResource->getFont().get();
		addResource (mCurrentFontResourceInstId, fontResource);
		
		fontResource->changedEvent.add([&]{ 
			auto resource = getFontResource();
			if (resource) {
				::SendMessage (mHWnd, WM_SETFONT, reinterpret_cast<WPARAM>(resource->getHFont()), TRUE);
			}
		});
	}
}

bool WindowBase::getStyleBit(DWORD flag) {
	LONG style = ::GetWindowLong (mHWnd, GWL_STYLE);
	
	return style & flag;
}

void WindowBase::setStyleBit(DWORD flag, bool value) {
	LONG style = ::GetWindowLong (mHWnd, GWL_STYLE);
	
	if (value) {
		style |= flag;
	} else {
		style &= ~flag;
	}
	
	::SetWindowLong (mHWnd, GWL_STYLE, style);
}

bool WindowBase::getExStyleBit(DWORD flag) {
	LONG style = ::GetWindowLong (mHWnd, GWL_EXSTYLE);
	
	return style & flag;
}

void WindowBase::setExStyleBit(DWORD flag, bool value) {
	LONG style = ::GetWindowLong (mHWnd, GWL_EXSTYLE);
	
	if (value) {
		style |= flag;
	} else {
		style &= ~flag;
	}
	
	::SetWindowLong (mHWnd, GWL_EXSTYLE, style);
	// ...important: Certain window data is cached, so changes you make using SetWindowLong 
	// will not take effect until you call the SetWindowPos function. Specifically, if you 
	// change any of the frame styles, you must call SetWindowPos with the SWP_FRAMECHANGED 
	// flag for the cache to be updated properly.
}

HWND WindowBase::getTopLevelHWnd() {
	return ::GetAncestor (mHWnd, GA_ROOT);
}

void WindowBase::destroy() {
	MessageDispatcher::getInstance().unregisterControllerByHandle (mHWnd);
	WindowsObject::destroy();
}

}


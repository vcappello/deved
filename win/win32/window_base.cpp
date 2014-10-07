#include "window_base.h"

#include "control_factory.h"

namespace win {

WindowBase::WindowBase(HWND hWnd) :
	mHWnd( hWnd ) {
}

WindowBase::~WindowBase() {
	::DestroyWindow (mHWnd);
}

Point WindowBase::getPosition() {
	HWND hWndParent = ::GetParent(mHWnd);
	POINT position = {0};

	::MapWindowPoints(mHWnd, hWndParent, &position, 1);
	
	return Point( position.x, position.y );	
}

void WindowBase::setPosition(const Point& value) {
	::SetWindowPos(mHWnd, 0, 
		value.x, value.y, 0, 0, 
		SWP_NOZORDER | SWP_NOSIZE);
}

Size WindowBase::getSize() {
	RECT rect;
	::GetWindowRect (mHWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	return Size( width, height );
}

void WindowBase::setSize(const Size& size) {
	::SetWindowPos(mHWnd, 0, 
		0, 0, size.width, size.height, 
		SWP_NOZORDER | SWP_NOMOVE);	
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

std::shared_ptr<FontResource> WindowBase::getFontResource() {
	return std::dynamic_pointer_cast<FontResource>(mResources[mCurrentFontResourceName]);
}

void WindowBase::setFontResource(std::shared_ptr<FontResource> fontResource) {
	::SendMessage (mHWnd, WM_SETFONT, reinterpret_cast<WPARAM>(fontResource->getHFont()), TRUE);

	if (!resourceExist (fontResource->getFont()->name())) {
		mCurrentFontResourceName = fontResource->getFont()->name();
		addResource (mCurrentFontResourceName, fontResource);
		
		fontResource->changedEvent.add([&]{ 
			auto resource = getFontResource();
			if (resource) {
				::SendMessage (mHWnd, WM_SETFONT, reinterpret_cast<WPARAM>(resource->getHFont()), TRUE);
			}
		});
	}
}

void WindowBase::destroy() {
	MessageDispatcher::getInstance().unregisterControllerByHandle (mHWnd);
	WindowsObject::destroy();
}

}


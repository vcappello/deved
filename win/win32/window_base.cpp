#include "window_base.h"

namespace win {

WindowBase::WindowBase(HWND hWnd) :
	mHWnd( hWnd ) {
}

WindowBase::~WindowBase() {
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
	//DWORD style = ::GetWindowLong (mHWnd, GWL_STYLE);
	if (value) {
		//style |= WS_VISIBLE;
		::ShowWindow (mHWnd, SW_SHOWNOACTIVATE);
	} else {
		//style &= !WS_VISIBLE;
		::ShowWindow (mHWnd, SW_HIDE);
	}
	//::SetWindowLong (mHWnd, GWL_STYLE, style);
}

}


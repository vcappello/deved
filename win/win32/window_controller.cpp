#include "window_controller.h"

#include <iostream>

namespace win {
	
WindowController::WindowController(HWND hWnd, std::shared_ptr<Window> window) :
	WindowBase( hWnd ),
	mWindow( window ) {
		
	mWindow->title.onPropertyChanged.add([&]{
		if (getText() != mWindow->title()) {
			setText (mWindow->title());
		}
	});
	
	mWindow->left.onPropertyChanged.add([&]{
		Point point = getPosition();
		if (point.x != mWindow->left()) {
			point.x = mWindow->left();
			setPosition (point);
		}
	});	
	
	mWindow->top.onPropertyChanged.add([&]{
		Point point = getPosition();
		if (point.y != mWindow->top()) {
			point.y = mWindow->top();
			setPosition (point);
		}
	});	
		
	mWindow->width.onPropertyChanged.add([&]{
		Size size = getSize();
		if (size.width != mWindow->width()) {
			size.width = mWindow->width();
			setSize (size);
		}
	});		
	
	mWindow->height.onPropertyChanged.add([&]{
		Size size = getSize();
		if (size.height != mWindow->height()) {
			size.height = mWindow->height();
			setSize (size);
		}
	});		
}

WindowController::~WindowController() {
}

Point WindowController::getPosition() {
	RECT rect;
	::GetWindowRect (mHWnd, &rect);
	
	return Point( rect.left, rect.top );
}

bool WindowController::handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult) {
	
	switch (message) {
		case WM_SETTEXT:
		{
			std::string text( (LPCTSTR)lParam );
			mWindow->title(text);
			break;
		}
		case WM_WINDOWPOSCHANGED:
		{
			WINDOWPOS* windowPos = (WINDOWPOS*)lParam;
			if (!(windowPos->flags & SWP_NOSIZE)) {
				mWindow->width (windowPos->cx);
				mWindow->height (windowPos->cy);
			}
			if (!(windowPos->flags & SWP_NOMOVE)) {
				mWindow->left (windowPos->x);
				mWindow->top (windowPos->y);
			}
			break;
		}
		case WM_DESTROY:
		{
			::PostQuitMessage(0);
			break;
		}
	}
	
	return false;
}

LRESULT WindowController::callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return ::DefWindowProc (hWnd, message, wParam, lParam);
}

}


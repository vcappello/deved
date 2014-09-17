#include "button_controller.h"
#include "message_dispatcher.h"

namespace win {
	
ButtonController::ButtonController(HWND hWnd, int commandId, std::shared_ptr<Button> button) :
	WindowBase( hWnd ),
	mCommandId( commandId ),
	mButton( button ),
	mOldWndProc( NULL )	{
	mButton->text.onPropertyChanged.add([&]{
		if (getText() != mButton->text()) {
			setText (mButton->text());
		}
	});
	
	mButton->left.onPropertyChanged.add([&]{
		Point point = getPosition();
		if (point.x != mButton->left()) {
			point.x = mButton->left();
			setPosition (point);
		}
	});	
	
	mButton->top.onPropertyChanged.add([&]{
		Point point = getPosition();
		if (point.y != mButton->top()) {
			point.y = mButton->top();
			setPosition (point);
		}
	});	
		
	mButton->width.onPropertyChanged.add([&]{
		Size size = getSize();
		if (size.width != mButton->width()) {
			size.width = mButton->width();
			setSize (size);
		}
	});		
	
	mButton->height.onPropertyChanged.add([&]{
		Size size = getSize();
		if (size.height != mButton->height()) {
			size.height = mButton->height();
			setSize (size);
		}
	});				
}

ButtonController::~ButtonController() {
	if (mOldWndProc) {
		SetWindowLongPtr (mHWnd, GWLP_WNDPROC, (LONG_PTR)mOldWndProc);
	}
}

void ButtonController::subclass() {
	mOldWndProc = (WNDPROC)SetWindowLongPtr (mHWnd, GWLP_WNDPROC, (LONG_PTR)MessageDispatcher::uniqueWndProc);
}

bool ButtonController::handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult) {
	switch (message) {
		case WM_SETTEXT:
		{
			std::string text( (LPCTSTR)lParam );
			mButton->text(text);
			break;
		}
		case WM_WINDOWPOSCHANGED:
		{
			WINDOWPOS* windowPos = (WINDOWPOS*)lParam;
			if (!(windowPos->flags & SWP_NOSIZE)) {
				mButton->width (windowPos->cx);
				mButton->height (windowPos->cy);
			}
			if (!(windowPos->flags & SWP_NOMOVE)) {
				mButton->left (windowPos->x);
				mButton->top (windowPos->y);
			}
			break;
		}
	}
	return false;
}

LRESULT ButtonController::callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return ::CallWindowProc (mOldWndProc, hWnd, message, wParam, lParam);
}

void ButtonController::handleCommand(WPARAM wParam, LPARAM lParam) {
}

}
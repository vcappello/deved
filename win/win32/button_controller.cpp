#include "button_controller.h"
#include "message_dispatcher.h"

namespace win {
	
ButtonController::ButtonController(HWND hWnd, int commandId, std::shared_ptr<Button> button) :
	WindowBase( hWnd ),
	mCommandId( commandId ),
	mButton( button ),
	mOldWndProc( NULL )	{
		
	mButton->text.changedEvent.add([&]{
		if (getText() != mButton->text()) {
			setText (mButton->text());
		}
	});
	
	mButton->left.changedEvent.add([&]{
		Point point = getPosition();
		if (point.x != mButton->left()) {
			point.x = mButton->left();
			setPosition (point);
		}
	});	
	
	mButton->top.changedEvent.add([&]{
		Point point = getPosition();
		if (point.y != mButton->top()) {
			point.y = mButton->top();
			setPosition (point);
		}
	});	
		
	mButton->width.changedEvent.add([&]{
		Size size = getSize();
		if (size.width != mButton->width()) {
			size.width = mButton->width();
			setSize (size);
		}
	});		
	
	mButton->height.changedEvent.add([&]{
		Size size = getSize();
		if (size.height != mButton->height()) {
			size.height = mButton->height();
			setSize (size);
		}
	});	

	mButton->visible.changedEvent.add([&] {
		if (isVisible() != mButton->visible()) {
			setVisible (mButton->visible());
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
		case WM_STYLECHANGED:
		{
			STYLESTRUCT* styleStruct = (STYLESTRUCT*)lParam;
			if ((styleStruct->styleOld & WS_VISIBLE) != (styleStruct->styleNew & WS_VISIBLE)) {
				mButton->visible (styleStruct->styleNew & WS_VISIBLE);
			}
		}		
	}
	return false;
}

LRESULT ButtonController::callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return ::CallWindowProc (mOldWndProc, hWnd, message, wParam, lParam);
}

void ButtonController::handleCommand(WPARAM wParam, LPARAM lParam) {
	int notification = HIWORD(wParam);
	switch (notification) {
		case BN_CLICKED:
		{
			mButton->clickedEvent.fire();
		}
	}
}

}
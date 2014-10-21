#include "button_controller.h"
#include "message_dispatcher.h"

namespace win {
	
ButtonController::ButtonController(HWND hWnd, int commandId, std::shared_ptr<Button> button) :
	WindowBase( hWnd ),
	mCommandId( commandId ),
	mButton( button ),
	mLayout( hWnd, button ),
	mOldWndProc( NULL )	{
		
	mButton->text.changedEvent.add([&]{
		if (getText() != mButton->text()) {
			setText (mButton->text());
		}
	});
	
	mButton->visible.changedEvent.add([&] {
		if (isVisible() != mButton->visible()) {
			setVisible (mButton->visible());
		}
	});	

	mButton->enabled.changedEvent.add([&] {
		if (isEnabled() != mButton->enabled()) {
			setEnabled (mButton->enabled());
		}
	});		
}

ButtonController::~ButtonController() {
	// Remove subclassing
	if (mOldWndProc) {
		SetWindowLongPtr (mHWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( mOldWndProc ));
	}
}

bool ButtonController::isDefault() {
	return getStyleBit (BS_DEFPUSHBUTTON);
}

void ButtonController::setDefault(bool value) {
	setStyleBit (BS_DEFPUSHBUTTON, value);
}

void ButtonController::subclass() {
	mOldWndProc = reinterpret_cast<WNDPROC>( 
		SetWindowLongPtr (mHWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( 
			MessageDispatcher::uniqueWndProc )) );
}

bool ButtonController::handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult) {
	switch (message) {
		case WM_SETTEXT:
		{
			std::string text( reinterpret_cast<LPCTSTR>( lParam ));
			mButton->text(text);
			break;
		}
		case WM_SETFONT:
		{
			HFONT hFont = reinterpret_cast<HFONT>( wParam );
			if (hFont != getFontResource()->getHFont()) {
				LOGFONT logFont;
				::GetObject (hFont, sizeof(logFont), &logFont);
				getFontResource()->updateModelFromLogFont (logFont);
			}
			break;
		}
		case WM_WINDOWPOSCHANGED:
		{
			WINDOWPOS* windowPos = reinterpret_cast<WINDOWPOS*>( lParam );
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
			STYLESTRUCT* styleStruct = reinterpret_cast<STYLESTRUCT*>( lParam );
			if ((styleStruct->styleOld & WS_DISABLED) != (styleStruct->styleNew & WS_DISABLED)) {
				mButton->enabled (!(styleStruct->styleNew & WS_DISABLED));
			}
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
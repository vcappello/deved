#include "label_controller.h"

#include <iostream>

namespace win {
	
LabelController::LabelController(HWND hWnd, int commandId, std::shared_ptr<Label> label) :
	WindowBase( hWnd ),
	mCommandId( commandId ),
	mLabel( label ),
	mLayout( hWnd, label ),
	mOldWndProc( NULL )	{
		
	mLabel->text.changedEvent.add([&]{
		if (getText() != mLabel->text()) {
			setText (mLabel->text());
		}
	});
	
	mLabel->visible.changedEvent.add([&] {
		if (isVisible() != mLabel->visible()) {
			setVisible (mLabel->visible());
		}
	});	

	mLabel->enabled.changedEvent.add([&] {
		if (isEnabled() != mLabel->enabled()) {
			setEnabled (mLabel->enabled());
		}
	});		

	mLabel->border.changedEvent.add([&] {
		std::cout << "mLabel->border.changedEvent" << std::endl;
		if (hasBorder() != mLabel->border()) {
			std::cout << "hasBorder() != mLabel->border(): " << hasBorder() << " != " << mLabel->border() << std::endl;
			setBorder (mLabel->border());
		}
	});
}

LabelController::~LabelController() {
	// Remove subclassing
	if (mOldWndProc) {
		SetWindowLongPtr (mHWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( mOldWndProc ));
	}
}

void LabelController::subclass() {
	mOldWndProc = reinterpret_cast<WNDPROC>( 
		SetWindowLongPtr (mHWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( 
			MessageDispatcher::uniqueWndProc )) );
}

bool LabelController::handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult) {
	switch (message) {
		case WM_SETTEXT:
		{
			std::string text( reinterpret_cast<LPCTSTR>( lParam ));
			mLabel->text(text);
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
				mLabel->width (windowPos->cx);
				mLabel->height (windowPos->cy);
			}
			if (!(windowPos->flags & SWP_NOMOVE)) {
				mLabel->left (windowPos->x);
				mLabel->top (windowPos->y);
			}
			break;
		}
		case WM_STYLECHANGED:
		{
			STYLESTRUCT* styleStruct = reinterpret_cast<STYLESTRUCT*>( lParam );
			if (wParam == (DWORD)GWL_STYLE) {
				if ((styleStruct->styleOld & WS_DISABLED) != (styleStruct->styleNew & WS_DISABLED)) {
					mLabel->enabled (!(styleStruct->styleNew & WS_DISABLED));
				}
				if ((styleStruct->styleOld & WS_VISIBLE) != (styleStruct->styleNew & WS_VISIBLE)) {
					mLabel->visible (styleStruct->styleNew & WS_VISIBLE);
				}
			} else if (wParam == (DWORD)GWL_EXSTYLE) {
				if ((styleStruct->styleOld & WS_EX_CLIENTEDGE) != (styleStruct->styleNew & WS_EX_CLIENTEDGE)) {
					mLabel->border (styleStruct->styleNew & WS_EX_CLIENTEDGE);
				}
			}
		}		
	}
	return false;
}

LRESULT LabelController::callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return ::CallWindowProc (mOldWndProc, hWnd, message, wParam, lParam);
}

void LabelController::handleCommand(WPARAM wParam, LPARAM lParam) {
}
	
}


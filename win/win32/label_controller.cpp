#include "label_controller.h"

namespace win {
	
LabelController::LabelController(HWND hWnd, int commandId, std::shared_ptr<Label> label) :
	WindowBase( hWnd ),
	mCommandId( commandId ),
	mLabel( label ),
	mLayout( hWnd, label )	{
		
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
		if (hasBorder() != mLabel->border()) {
			setBorder (mLabel->border());
		}
	});
}

LabelController::~LabelController() {
}

void LabelController::subclass() {
	mSubclassHandler = SubclassHandler::create (mHWnd);
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
	if (mSubclassHandler) {
		return mSubclassHandler->callDefWindowProc (hWnd, message, wParam, lParam);
	}
	return 0;
}

void LabelController::handleCommand(WPARAM wParam, LPARAM lParam) {
}
	
}


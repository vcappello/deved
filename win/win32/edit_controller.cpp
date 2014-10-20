#include "edit_controller.h"

namespace win {
	
EditController::EditController(HWND hWnd, int commandId, std::shared_ptr<Edit> edit) :
	WindowBase( hWnd ),
	mCommandId( commandId ),
	mEdit( edit ),
	mLayout( hWnd, edit ),
	mOldWndProc( NULL )	{
		
	mEdit->text.changedEvent.add([&]{
		if (getText() != mEdit->text()) {
			setText (mEdit->text());
		}
	});
	
	mEdit->visible.changedEvent.add([&] {
		if (isVisible() != mEdit->visible()) {
			setVisible (mEdit->visible());
		}
	});	

	mEdit->enabled.changedEvent.add([&] {
		if (isEnabled() != mEdit->enabled()) {
			setEnabled (mEdit->enabled());
		}
	});		

	mEdit->multiline.changedEvent.add([&] {
		if (isMultiline() != mEdit->multiline()) {
			setMultiline (mEdit->multiline());
		}
	});

	mEdit->border.changedEvent.add([&] {
		if (hasBorder() != mEdit->border()) {
			setBorder (mEdit->border());
		}
	});
}

EditController::~EditController() {
	// Remove subclassing
	if (mOldWndProc) {
		SetWindowLongPtr (mHWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( mOldWndProc ));
	}
}

bool EditController::isMultiline() {
	return getStyleBit (ES_MULTILINE);
}

void EditController::setMultiline(bool value) {
	setStyleBit (ES_MULTILINE, value);
}

void EditController::subclass() {
	mOldWndProc = reinterpret_cast<WNDPROC>( 
		SetWindowLongPtr (mHWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( 
			MessageDispatcher::uniqueWndProc )) );
}

bool EditController::handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult) {
	switch (message) {
		case WM_SETTEXT:
		{
			std::string text( reinterpret_cast<LPCTSTR>( lParam ));
			mEdit->text(text);
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
				mEdit->width (windowPos->cx);
				mEdit->height (windowPos->cy);
			}
			if (!(windowPos->flags & SWP_NOMOVE)) {
				mEdit->left (windowPos->x);
				mEdit->top (windowPos->y);
			}
			break;
		}
		case WM_STYLECHANGED:
		{
			STYLESTRUCT* styleStruct = reinterpret_cast<STYLESTRUCT*>( lParam );
			if (wParam == (DWORD)GWL_STYLE) {
				if ((styleStruct->styleOld & ES_MULTILINE) != (styleStruct->styleNew & ES_MULTILINE)) {
					mEdit->multiline (styleStruct->styleNew & ES_MULTILINE);
				}
				if ((styleStruct->styleOld & WS_DISABLED) != (styleStruct->styleNew & WS_DISABLED)) {
					mEdit->enabled (!(styleStruct->styleNew & WS_DISABLED));
				}
				if ((styleStruct->styleOld & WS_VISIBLE) != (styleStruct->styleNew & WS_VISIBLE)) {
					mEdit->visible (styleStruct->styleNew & WS_VISIBLE);
				}
			} else if (wParam == (DWORD)GWL_EXSTYLE) {
				if ((styleStruct->styleOld & WS_EX_CLIENTEDGE) != (styleStruct->styleNew & WS_EX_CLIENTEDGE)) {
					mEdit->border (styleStruct->styleNew & WS_EX_CLIENTEDGE);
				}
			}
		}		
	}
	return false;
}

LRESULT EditController::callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return ::CallWindowProc (mOldWndProc, hWnd, message, wParam, lParam);
}

void EditController::handleCommand(WPARAM wParam, LPARAM lParam) {
}
	
}


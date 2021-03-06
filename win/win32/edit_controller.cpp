#include "edit_controller.h"

namespace win {
	
EditController::EditController(HWND hWnd, int commandId, std::shared_ptr<Edit> edit) :
	WindowBase( hWnd ),
	mCommandId( commandId ),
	mEdit( edit ),
	mLayout( hWnd, edit ) {
		
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
	
	mEdit->textColor.changedEvent.add([&] {
		redraw();
	});
	
	mEdit->backgroundColor.changedEvent.add([&] {
		redraw();
	});
}

EditController::~EditController() {
}

bool EditController::isMultiline() {
	return getStyleBit (ES_MULTILINE);
}

void EditController::setMultiline(bool value) {
	setStyleBit (ES_MULTILINE, value);
}

void EditController::subclass() {
	mSubclassHandler = SubclassHandler::create (mHWnd);
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
			getFontResource()->setHFont (hFont);
			break;
		}
		case WM_CTLCOLORSTATIC:
		case WM_CTLCOLOREDIT:
		{
			HDC hDC = reinterpret_cast<HDC>( wParam );
			if (mEdit->textColor() != nullptr) {
				::SetTextColor (hDC, mEdit->textColor()->value());
			} else {
				::SetTextColor (hDC, ::GetSysColor (COLOR_WINDOWTEXT));
			}
			if (mEdit->backgroundColor() != nullptr) {
				::SetBkColor (hDC, mEdit->backgroundColor()->value());
				mBackgroundBrush = std::unique_ptr<GdiObject<HBRUSH>>( 
					new GdiObject<HBRUSH>( ::CreateSolidBrush(
						mEdit->backgroundColor()->value())));
				lResult = reinterpret_cast<LRESULT>(mBackgroundBrush->getHandle());
			} else {
				mBackgroundBrush = nullptr;
				::SetBkColor (hDC, ::GetSysColor (COLOR_WINDOW));
				lResult = reinterpret_cast<LRESULT>(::GetSysColorBrush (COLOR_WINDOW));
				return true;
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
	if (mSubclassHandler) {
		return mSubclassHandler->callDefWindowProc (hWnd, message, wParam, lParam);
	}
	return 0;
}

void EditController::handleCommand(WPARAM wParam, LPARAM lParam) {
	int notification = HIWORD(wParam);
	switch (notification) {
		case EN_CHANGE:
		{
			std::string value = getText();
			mEdit->text (value);
		}
	}		
}
	
}


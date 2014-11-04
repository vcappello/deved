#include "list_box_controller.h"

namespace win {
	
ListBoxController::ListBoxController(HWND hWnd, int commandId, std::shared_ptr<ListBox> listBox) :
	WindowBase( hWnd ),
	mCommandId( commandId ),
	mListBox( listBox ),
	mLayout( hWnd, listBox ) {
		
	mListBox->visible.changedEvent.add([&] {
		if (isVisible() != mListBox->visible()) {
			setVisible (mListBox->visible());
		}
	});	

	mListBox->enabled.changedEvent.add([&] {
		if (isEnabled() != mListBox->enabled()) {
			setEnabled (mListBox->enabled());
		}
	});
	
	mListBox->listItems.itemAddedEvent.add([&] (std::shared_ptr<ListItem> listItem) {
		// TODO: implement this!
	});
	
	mListBox->listItems.itemRemovedEvent.add([&] (std::shared_ptr<ListItem> listItem) {
		// TODO: implement this!
	});	
}

ListBoxController::~ListBoxController() {
}

void ListBoxController::subclass() {
	mSubclassHandler = SubclassHandler::create (mHWnd);
}

bool ListBoxController::handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult) {
	bool handled = false;
	switch (message) {
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
				mListBox->width (windowPos->cx);
				mListBox->height (windowPos->cy);
			}
			if (!(windowPos->flags & SWP_NOMOVE)) {
				mListBox->left (windowPos->x);
				mListBox->top (windowPos->y);
			}
			break;
		}
		case WM_STYLECHANGED:
		{
			STYLESTRUCT* styleStruct = reinterpret_cast<STYLESTRUCT*>( lParam );
			if ((styleStruct->styleOld & WS_DISABLED) != (styleStruct->styleNew & WS_DISABLED)) {
				mListBox->enabled (!(styleStruct->styleNew & WS_DISABLED));
			}
			if ((styleStruct->styleOld & WS_VISIBLE) != (styleStruct->styleNew & WS_VISIBLE)) {
				mListBox->visible (styleStruct->styleNew & WS_VISIBLE);
			}
		}		
	}
	return handled;
}

LRESULT ListBoxController::callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if (mSubclassHandler) {
		return mSubclassHandler->callDefWindowProc (hWnd, message, wParam, lParam);
	}
	return 0;
}

void ListBoxController::handleCommand(WPARAM wParam, LPARAM lParam) {
}

}


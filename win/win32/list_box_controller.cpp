#include "list_box_controller.h"

#include "list_item_factory.h"

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
		auto listItemController = createListItemController (shared_from_this(), listItem);
		addListItemController (listItemController);
	});
	
	mListBox->listItems.itemRemovedEvent.add([&] (std::shared_ptr<ListItem> listItem) {
		// If the item to remove is the selected one then clear selection
		if (mListBox->selectedItem() == listItem) {
			mListBox->selectedItem (nullptr);
		}
		
		auto listItemController = mListItemControllers[listItem.get()];
		
		LRESULT result = ::SendMessage (mHWnd, LB_DELETESTRING, listItemController->getIndex(), 0);
		if (result == LB_ERR) {
			throw Error( "Can not delete list item (LB_DELETESTRING)" );
		}	
				
		mListItemControllers.erase (listItem.get());
		
		rebuildIndexes();
	});	
}

ListBoxController::~ListBoxController() {
}

void ListBoxController::addListItemController(std::shared_ptr<ListItemController> listItemController) {
	mListItemControllers.insert (std::make_pair( listItemController->getListItem().get(), listItemController ));
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
			getFontResource()->setHFont (hFont);
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
	int notification = HIWORD(wParam);
	switch (notification) {
		case LBN_SELCHANGE:
		{
			int index = getCurrentSelection();
			if (index != LB_ERR) {
				listItemKeyT selectedKey = getItemKey (index);
				mListBox->selectedItem (mListItemControllers[selectedKey]->getListItem());
			} else {
				mListBox->selectedItem (nullptr);
			}
			break;
		}
		case LBN_SELCANCEL:
		{
			mListBox->selectedItem (nullptr);
			break;
		}
	}	
}

int ListBoxController::getCurrentSelection() {
	int index = ::SendMessage (mHWnd, LB_GETCURSEL, 0, 0);
	
	return index;	
}

int ListBoxController::getItemsCount() {
	int itemsCount = ::SendMessage (mHWnd, LB_GETCOUNT, 0, 0);
	if (itemsCount == LB_ERR) {
		throw Error( "Can not retrieve items count (LB_GETCOUNT)" );
	}
	
	return itemsCount;
}

ListBoxController::listItemKeyT ListBoxController::getItemKey(int index) {
	LRESULT key = ::SendMessage (mHWnd, LB_GETITEMDATA, index, 0);
	if (key == LB_ERR) {
		throw Error( "Can not retrieve item key (LB_GETITEMDATA)" );
	}
	
	return reinterpret_cast<listItemKeyT>( key );
}

void ListBoxController::rebuildIndexes() {
	for (int i = 0; i < getItemsCount(); i++) {
		listItemKeyT key = getItemKey (i);
		mListItemControllers[key]->setIndex (i);
	}
}

}


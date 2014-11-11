#include "text_list_item_controller.h"

namespace win {
	
TextListItemController::TextListItemController(int index, HWND hWndListBox, std::shared_ptr<TextListItem> textListItem) :
	ListItemController( index, hWndListBox ),
	mTextListItem( textListItem ) {
		
	mTextListItem->text.changedEvent.add([&] {
		if (getListItemText() != mTextListItem->text()) {
			setListItemText (mTextListItem->text());
		}
	});			
}

TextListItemController::~TextListItemController() {
}

std::string TextListItemController::getText() const {
	return mTextListItem->text();
}
	
std::shared_ptr<ListItem> TextListItemController::getListItem() const {
	return mTextListItem;
}

}


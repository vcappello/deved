#include "list_item_controller.h"

namespace win {

ListItemController::ListItemController(int index, HWND hWndListBox) :
	mIndex( index ),
	mHWndListBox( hWndListBox ) {
}

ListItemController::~ListItemController() {
}

std::string ListItemController::getListItemText() {
	int len = ::SendMessage(mHWndListBox, LB_GETTEXTLEN, mIndex, 0);
	if (len == LB_ERR) {
		throw Error( "Can not retrieve list item text (LB_GETTEXTLEN)" );
	}
	
	std::string text;
	text.reserve (len + 1); // reserve the space for the NULL character
	
	LRESULT result = ::SendMessage (mHWndListBox, LB_GETTEXT, mIndex, reinterpret_cast<LPARAM>( text.c_str() ));
	if (result == LB_ERR) {
		throw Error( "Can not retrieve list item text (LB_GETTEXT)" );
	}
	
	return text;
}

void ListItemController::setListItemText(const std::string& value) {
	int selectedIndex = ::SendMessage (mHWndListBox, LB_GETCURSEL, 0, 0);
	if (selectedIndex == LB_ERR) {
		throw Error( "Can not retrieve current selection (LB_GETCURSEL)" );
	}
	
	LRESULT result = ::SendMessage (mHWndListBox, LB_DELETESTRING, mIndex, 0);
	if (result == LB_ERR) {
		throw Error( "Can not set list item text (LB_DELETESTRING)" );
	}	
	
	result = ::SendMessage (mHWndListBox, LB_INSERTSTRING, mIndex, reinterpret_cast<LPARAM>( value.c_str() ));
	if (result == LB_ERR) {
		throw Error( "Can not set list item text (LB_INSERTSTRING)" );
	}

	::SendMessage (mHWndListBox, LB_SETITEMDATA, mIndex, reinterpret_cast<LPARAM>(getListItem().get()));

	// Restore selection
	if (selectedIndex == mIndex) {
		result = ::SendMessage (mHWndListBox, LB_SETCURSEL, selectedIndex, 0);
		if (result == LB_ERR) {
			throw Error( "Can not retrieve current selection (LB_SETCURSEL)" );
		}		
	}
}

}


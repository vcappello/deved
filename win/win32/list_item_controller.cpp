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
	// TODO: preserve selection, if the item that is changing is selected
	LRESULT result = ::SendMessage (mHWndListBox, LB_DELETESTRING, mIndex, 0);
	if (result == LB_ERR) {
		throw Error( "Can not set list item text (LB_DELETESTRING)" );
	}	
	
	int newIndex = ::SendMessage (mHWndListBox, LB_INSERTSTRING, mIndex, reinterpret_cast<LPARAM>( value.c_str() ));
	if (newIndex == LB_ERR) {
		throw Error( "Can not set list item text (LB_INSERTSTRING)" );
	}
}

}


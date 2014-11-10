/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_LIST_ITEM_CONTROLLER_H
#define WIN_WIN32_LIST_ITEM_CONTROLLER_H

#include <win/list_item.h>
#include <win/error.h>

#include <string>
#include <windows.h>

namespace win {

class ListItemController {
public:
	ListItemController(int index, HWND hWndListBox);
	virtual ~ListItemController();

	int getIndex() const { return mIndex; }
	void setIndex(int value) { mIndex = value; }
	
	virtual std::string getText() = 0;
	
protected:
	int mIndex;
	HWND mHWndListBox;

protected:
	std::string getListItemText();
	void setListItemText(const std::string& value);	
};

}

#endif // WIN_WIN32_LIST_ITEM_CONTROLLER_H

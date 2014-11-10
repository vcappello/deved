/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_TEXT_LIST_ITEM_CONTROLLER_H
#define WIN_WIN32_TEXT_LIST_ITEM_CONTROLLER_H

#include "list_item_controller.h"
#include <win/text_list_item.h>

#include <memory>
#include <string>
#include <windows.h>

namespace win {

class TextListItemController : public ListItemController {
public:
	TextListItemController(int index, HWND hWndListBox, std::shared_ptr<TextListItem> textListItem);
	virtual ~TextListItemController();

	virtual std::string getText() const;
	
protected:
	std::shared_ptr<TextListItem> mTextListItem;
};

}

#endif // WIN_WIN32_TEXT_LIST_ITEM_CONTROLLER_H

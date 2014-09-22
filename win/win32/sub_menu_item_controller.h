/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_SUB_MENU_ITEM_CONTROLLER_H
#define WIN_WIN32_SUB_MENU_ITEM_CONTROLLER_H

#include <win/sub_menu_item.h>

#include <memory>
#include <windows.h>

namespace win {

class SubMenuItemController {
public:
	SubMenuItemController(HMENU hMenuParent, std::shared_ptr<SubMenuItem> subMenuItem);
	virtual ~SubMenuItemController();
	
	HMENU getHMenu() { return mHMenu; }
	
public:
	HMENU mHMenuParent;
	std::shared_ptr<SubMenuItem> mSubMenuItem;
	HMENU mHMenu;
};

}

#endif // WIN_WIN32_SUB_MENU_ITEM_CONTROLLER_H


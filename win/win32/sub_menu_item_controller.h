/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_SUB_MENU_ITEM_CONTROLLER_H
#define WIN_WIN32_SUB_MENU_ITEM_CONTROLLER_H

#include "menu_item_controller_container.h"
#include "menu_item_controller_base.h"
#include <win/sub_menu_item.h>
#include "control_factory.h"

#include <memory>
#include <windows.h>

namespace win {

class SubMenuItemController : public MenuItemControllerContainer,
                              public MenuItemControllerBase,
                              public std::enable_shared_from_this<SubMenuItemController> {
public:
	SubMenuItemController(HMENU hMenuParent, int commandId, std::shared_ptr<SubMenuItem> subMenuItem);
	virtual ~SubMenuItemController();
	
	HMENU getHMenu() { return mHMenu; }
	
	// IMenuItemController implementations
	std::shared_ptr<MenuItem> getMenuItem() { return mSubMenuItem; }
	
public:
	std::shared_ptr<SubMenuItem> mSubMenuItem;
	HMENU mHMenu;
};

}

#endif // WIN_WIN32_SUB_MENU_ITEM_CONTROLLER_H


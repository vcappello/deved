/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_SUB_MENU_ITEM_CONTROLLER_H
#define WIN_WIN32_SUB_MENU_ITEM_CONTROLLER_H

#include "menu_item_controller_base.h"
#include "i_menu_item_controller_container.h"
#include <win/sub_menu_item.h>
#include "control_factory.h"

#include <memory>
#include <windows.h>

namespace win {

class SubMenuItemController : public MenuItemControllerBase,
                              public IMenuItemControllerContainer,
                              public std::enable_shared_from_this<SubMenuItemController> {
public:
	SubMenuItemController(HMENU hMenuParent, int commandId, std::shared_ptr<SubMenuItem> subMenuItem);
	virtual ~SubMenuItemController();
	
	/** @name MenuItemControllerBase implementations
	 */
	///@{ 	
	std::shared_ptr<MenuItem> getMenuItem() { return mSubMenuItem; }
	///@}
	
	/** @name IMenuItemControllerContainer implementations
	 */
	///@{ 
	HMENU getHMenu() { return mHMenu; }
	
	void addMenuItem(std::shared_ptr<MenuItemControllerBase> menuItemController);
	///@}	
	
public:
	std::shared_ptr<SubMenuItem> mSubMenuItem;
	HMENU mHMenu;
};

}

#endif // WIN_WIN32_SUB_MENU_ITEM_CONTROLLER_H


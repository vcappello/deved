/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_I_MENU_ITEM_CONTROLLER_CONTAINER_H
#define WIN_WIN32_I_MENU_ITEM_CONTROLLER_CONTAINER_H

#include "menu_item_controller_base.h"

#include <memory>
#include <windows.h>

namespace win {

class IMenuItemControllerContainer {
public:
	IMenuItemControllerContainer() {
	}
	virtual ~IMenuItemControllerContainer() {
	}
	
	virtual HMENU getHMenu() = 0;

	virtual void addMenuItem(std::shared_ptr<MenuItemControllerBase> menuItem) = 0;

public:
};

}

#endif // WIN_WIN32_I_MENU_ITEM_CONTROLLER_CONTAINER_H


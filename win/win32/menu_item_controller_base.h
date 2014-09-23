/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_MENU_ITEM_CONTROLLER_BASE_H
#define WIN_WIN32_MENU_ITEM_CONTROLLER_BASE_H

#include <win/menu_item.h>

#include <memory>
#include <windows.h>

namespace win {

class MenuItemControllerBase {
public:
	MenuItemControllerBase();
	virtual ~MenuItemControllerBase();
	
	virtual std::shared_ptr<MenuItem> getMenuItem() = 0;

public:
};

}

#endif // WIN_WIN32_MENU_ITEM_CONTROLLER_BASE_H


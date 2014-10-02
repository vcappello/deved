/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_MENU_ITEM_CONTROLLER_CONTAINER_H
#define WIN_WIN32_MENU_ITEM_CONTROLLER_CONTAINER_H

#include "windows_object.h"
#include "menu_item_controller_base.h"

#include <vector>
#include <memory>
#include <windows.h>

namespace win {

class MenuItemControllerContainer : public WindowsObject {
public:
	MenuItemControllerContainer();
	virtual ~MenuItemControllerContainer();
	
	virtual HMENU getHMenu() = 0;

public:
};

}

#endif // WIN_WIN32_MENU_ITEM_CONTROLLER_CONTAINER_H


/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_MENU_BAR_CONTROLLER_H
#define WIN_WIN32_MENU_BAR_CONTROLLER_H

#include "windows_object.h"
#include "i_menu_item_controller_container.h"
#include "control_factory.h"
#include <win/menu_bar.h>

#include <memory>
#include <windows.h>

namespace win {

class MenuBarController : public WindowsObject,
                          public IMenuItemControllerContainer,
                          public std::enable_shared_from_this<MenuBarController> {
public:
	MenuBarController(std::shared_ptr<MenuBar> menuBar);
	virtual ~MenuBarController();
	
	/** @name IMenuItemControllerContainer implementations
	 */
	///@{ 
	HMENU getHMenu() { return mHMenu; }
	
	void addMenuItem(const std::string& name, std::shared_ptr<MenuItemControllerBase> menuItem);
	///@}
	
public:
	HMENU mHMenu;
	std::shared_ptr<MenuBar> mMenuBar;
};

}

#endif // WIN_WIN32_MENU_BAR_CONTROLLER_H


/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_MENU_BAR_CONTROLLER_H
#define WIN_WIN32_MENU_BAR_CONTROLLER_H

#include "menu_item_controller_container.h"
#include "i_windows_object.h"
#include "control_factory.h"
#include <win/menu_bar.h>

#include <memory>
#include <windows.h>

namespace win {

class MenuBarController : public MenuItemControllerContainer,
						  public IWindowsObject,
                          public std::enable_shared_from_this<MenuBarController> {
public:
	MenuBarController(std::shared_ptr<MenuBar> menuBar);
	virtual ~MenuBarController();
	
	/** @name MenuItemControllerContainer implementations
	 */
	///@{ 
	HMENU getHMenu() { return mHMenu; }
	///@}
	
	/** @name IWindowsObject implementations
	 */
	///@{ 
	void destroy();
	///@}
	
public:
	HMENU mHMenu;
	std::shared_ptr<MenuBar> mMenuBar;
	std::map<std::string, std::shared_ptr<IWindowsObject>> mChildrenObjects;
};

}

#endif // WIN_WIN32_MENU_BAR_CONTROLLER_H


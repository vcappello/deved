/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_MENU_BAR_CONTROLLER_H
#define WIN_WIN32_MENU_BAR_CONTROLLER_H

#include <win/menu_bar.h>

#include <memory>
#include <windows.h>

namespace win {

class MenuBarController {
public:
	MenuBarController(std::shared_ptr<MenuBar> menuBar);
	virtual ~MenuBarController();
	
	HMENU getHMenu() { return mHMenu; }
	
public:
	HMENU mHMenu;
	std::shared_ptr<MenuBar> mMenuBar;
};

}

#endif // WIN_WIN32_MENU_BAR_CONTROLLER_H


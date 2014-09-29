/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_CONTROL_FACTORY_H
#define WIN_CONTROL_FACTORY_H

#include <win/control.h>
#include <win/button.h>
#include <win/menu_bar.h>
#include <win/command_menu_item.h>
#include <win/sub_menu_item.h>

#include <memory>
#include <windows.h>

namespace win {

class WindowController; // Forward declaration
class MenuItemControllerContainer; // Forward declaration
	
void createControl(std::shared_ptr<WindowController> windowController, std::shared_ptr<Control> control);

void createButtonControl(std::shared_ptr<WindowController> windowController, std::shared_ptr<Button> button);

void createMenuBarControl(std::shared_ptr<WindowController> windowController, std::shared_ptr<MenuBar> menuBar);

void createMenuItem(std::shared_ptr<MenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<MenuItem> menuItem);

void createCommandMenuItem(std::shared_ptr<MenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<CommandMenuItem> commandMenuItem);

void createSubMenuItem(std::shared_ptr<MenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<SubMenuItem> subMenuItem);

}

#endif // WIN_CONTROL_FACTORY_H


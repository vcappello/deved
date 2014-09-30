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

class IWindowsObject; // Forward declaration
class WindowController; // Forward declaration
class ButtonController; // Forward declaration
class MenuBarController; // Forward declaration
class MenuItemControllerContainer; // Forward declaration
class MenuItemControllerBase; // Forward declaration
class CommandMenuItemController; // Forward declaration
class SubMenuItemController; // Forward declaration
	
std::shared_ptr<IWindowsObject> createControl(std::shared_ptr<WindowController> windowController, std::shared_ptr<Control> control);

std::shared_ptr<ButtonController> createButtonControl(std::shared_ptr<WindowController> windowController, std::shared_ptr<Button> button);

std::shared_ptr<MenuBarController> createMenuBarControl(std::shared_ptr<WindowController> windowController, std::shared_ptr<MenuBar> menuBar);

std::shared_ptr<MenuItemControllerBase> createMenuItem(std::shared_ptr<MenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<MenuItem> menuItem);

std::shared_ptr<CommandMenuItemController> createCommandMenuItem(std::shared_ptr<MenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<CommandMenuItem> commandMenuItem);

std::shared_ptr<SubMenuItemController> createSubMenuItem(std::shared_ptr<MenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<SubMenuItem> subMenuItem);

}

#endif // WIN_CONTROL_FACTORY_H


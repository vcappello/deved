/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_CONTROL_FACTORY_H
#define WIN_CONTROL_FACTORY_H

#include <win/window.h>
#include <win/control.h>
#include <win/button.h>
#include <win/edit.h>
#include <win/menu_bar.h>
#include <win/command_menu_item.h>
#include <win/sub_menu_item.h>
#include <win/font.h>
#include <win/create_window.h>

#include <memory>
#include <windows.h>

namespace win {

/** @name Forward declarations
 */
///@{ 
class WindowsObject; 
class WindowController; 
class ButtonController; 
class EditController;
class MenuBarController; 
class IMenuItemControllerContainer; 
class MenuItemControllerBase; 
class CommandMenuItemController; 
class SubMenuItemController; 
class FontResource; 
///@}

// TODO: need to refactor, rename this functions *Controller	
std::shared_ptr<WindowsObject> createControl(std::shared_ptr<WindowController> windowController, std::shared_ptr<Control> control);

std::shared_ptr<ButtonController> createButtonControl(std::shared_ptr<WindowController> windowController, std::shared_ptr<Button> button);

std::shared_ptr<EditController> createEditControl(std::shared_ptr<WindowController> windowController, std::shared_ptr<Edit> edit);

std::shared_ptr<MenuBarController> createMenuBarControl(std::shared_ptr<WindowController> windowController, std::shared_ptr<MenuBar> menuBar);

std::shared_ptr<MenuItemControllerBase> createMenuItem(std::shared_ptr<IMenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<MenuItem> menuItem);

std::shared_ptr<CommandMenuItemController> createCommandMenuItem(std::shared_ptr<IMenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<CommandMenuItem> commandMenuItem);

std::shared_ptr<SubMenuItemController> createSubMenuItem(std::shared_ptr<IMenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<SubMenuItem> subMenuItem);

std::shared_ptr<WindowController> createWindowController(HWND hWnd, std::shared_ptr<Window> window);

HFONT createHFont(std::shared_ptr<Font> font);

std::shared_ptr<Font> createFont(const LOGFONT& logFont);

std::shared_ptr<FontResource> createFontResource(std::shared_ptr<Font> font);

}

#endif // WIN_CONTROL_FACTORY_H


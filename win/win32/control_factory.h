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
#include <win/label.h>
#include <win/group_box.h>
#include <win/menu_bar.h>
#include <win/command_menu_item.h>
#include <win/sub_menu_item.h>
#include <win/font.h>
#include <win/create_window.h>

#include "window_container_base.h"

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
class LabelController;
class GroupBoxController;	
class MenuBarController;
class IMenuItemControllerContainer; 
class MenuItemControllerBase; 
class CommandMenuItemController; 
class SubMenuItemController; 
class FontResource; 
///@}

std::shared_ptr<WindowsObject> createController(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<Control> control);

std::shared_ptr<ButtonController> createButtonController(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<Button> button);

std::shared_ptr<EditController> createEditController(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<Edit> edit);

std::shared_ptr<LabelController> createLabelController(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<Label> label);

std::shared_ptr<GroupBoxController> createGroupBoxController(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<GroupBox> groupBox);

std::shared_ptr<MenuBarController> createMenuBarController(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<MenuBar> menuBar);

std::shared_ptr<MenuItemControllerBase> createMenuItemController(std::shared_ptr<IMenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<MenuItem> menuItem);

std::shared_ptr<CommandMenuItemController> createCommandMenuItemController(std::shared_ptr<IMenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<CommandMenuItem> commandMenuItem);

std::shared_ptr<SubMenuItemController> createSubMenuItemController(std::shared_ptr<IMenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<SubMenuItem> subMenuItem);

std::shared_ptr<WindowController> createWindowController(HWND hWnd, std::shared_ptr<Window> window);

std::shared_ptr<WindowController> findWindowControllerFromChild(std::shared_ptr<WindowBase> childController);

HFONT createHFont(std::shared_ptr<Font> font);

std::shared_ptr<Font> createFont(const LOGFONT& logFont);

std::shared_ptr<FontResource> createFontResource(std::shared_ptr<Font> font);

}

#endif // WIN_CONTROL_FACTORY_H


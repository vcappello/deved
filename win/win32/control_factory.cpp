#include "control_factory.h"

#include "window_controller.h"
#include "button_controller.h"
#include "menu_bar_controller.h"
#include "command_menu_item_controller.h"
#include "sub_menu_item_controller.h"
#include "message_dispatcher.h"
#include "font_resource.h"

namespace win {

int createControlId() {
	static int controlIdCounter = 100;
	return controlIdCounter++;
}
	
std::shared_ptr<WindowsObject> createControl(std::shared_ptr<WindowController> windowController, std::shared_ptr<Control> control) {
	std::shared_ptr<WindowsObject> object;
	if (control->getType() == "Button") {
		auto buttonControl = std::dynamic_pointer_cast<Button>(control);
		if (!buttonControl) {
			throw Error( "Can not convert control to 'Button'" );
		}
		object = createButtonControl (windowController, buttonControl);
	} else if (control->getType() == "MenuBar") {
		auto menuBarControl = std::dynamic_pointer_cast<MenuBar>(control);
		if (!menuBarControl) {
			throw Error( "Can not convert control to 'MenuBar'" );
		}
		object = createMenuBarControl (windowController, menuBarControl);
	}
	return object;
}

std::shared_ptr<ButtonController> createButtonControl(std::shared_ptr<WindowController> windowController, std::shared_ptr<Button> button) {
	HINSTANCE hInstance = ::GetModuleHandle(NULL);

	DWORD window_style_ex = 0;
	DWORD window_style = WS_TABSTOP | WS_CHILD;
	
	if (button->visible())
		window_style |= WS_VISIBLE;
	
	int controlId = createControlId();
	HWND hWnd = CreateWindowEx (
					window_style_ex,
	                "BUTTON",
	                button->text().c_str(),
	                window_style,
					button->left(),
					button->top(),
					button->width(),
					button->height(),
	                windowController->getHWnd(),
	                (HMENU)(intptr_t)controlId,
	                hInstance,
	                NULL);

	if (!hWnd) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}	
	
	// Create ButtonController instance
	auto controller = std::make_shared<ButtonController>( hWnd, controlId, button );
	MessageDispatcher::getInstance().registerController (controller);
	
	if (button->font()) {
		auto fontResource = createFontResource (button->font());
		controller->setFont (fontResource);
	}
	
	// Subclass window
	controller->subclass();
	
	return controller;
}

std::shared_ptr<MenuBarController> createMenuBarControl(std::shared_ptr<WindowController> windowController, std::shared_ptr<MenuBar> menuBar) {
	auto controller = std::make_shared<MenuBarController>( menuBar );
	
	// Create children menu items	
	for (auto menuItem : menuBar->menuItems) {
		createMenuItem (controller, menuItem.second);
	}
	
	windowController->setMenuBarController (controller);
	
	return controller;
}

std::shared_ptr<MenuItemControllerBase> createMenuItem(std::shared_ptr<IMenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<MenuItem> menuItem) {
	std::shared_ptr<MenuItemControllerBase> menuItemControllerBase;
	if (menuItem->getType() == "CommandMenuItem") {
		
		auto commandMenuItem = std::dynamic_pointer_cast<CommandMenuItem>(menuItem);
		if (!commandMenuItem) {
			throw Error( "Can not convert control to 'CommandMenuItem'" );
		}			
		menuItemControllerBase = createCommandMenuItem (menuItemControllerContainer, commandMenuItem);
		
	} else if (menuItem->getType() == "SubMenuItem") {
		
		auto subMenuItem = std::dynamic_pointer_cast<SubMenuItem>(menuItem);
		if (!subMenuItem) {
			throw Error( "Can not convert control to 'SubMenuItem'" );
		}				
		menuItemControllerBase = createSubMenuItem (menuItemControllerContainer, subMenuItem);
		
	}
	
	return menuItemControllerBase;
}

std::shared_ptr<CommandMenuItemController> createCommandMenuItem(std::shared_ptr<IMenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<CommandMenuItem> commandMenuItem) {
	// Get a new control ID for the menu item
	int controlId = createControlId();
	
	// Fill MENUITEMINFO structure
	MENUITEMINFO mii = {0};
	mii.cbSize = sizeof(MENUITEMINFO);

	mii.fMask = MIIM_STRING | MIIM_ID | MIIM_FTYPE; 
    mii.fType = MFT_STRING;
	mii.wID = controlId;
    mii.dwTypeData = (LPSTR)commandMenuItem->text().c_str();
	mii.cch = commandMenuItem->text().size();
	
	if (!commandMenuItem->enabled()) {
		mii.fState = MFS_DISABLED;
		mii.fMask |= MIIM_STATE;
	}
	
	// Insert the new item as last item of the parent container	
	int position = ::GetMenuItemCount(menuItemControllerContainer->getHMenu());
	BOOL res = ::InsertMenuItem(menuItemControllerContainer->getHMenu(), position, TRUE, &mii); 	
	
	if (!res) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}

	auto controller = std::make_shared<CommandMenuItemController>( menuItemControllerContainer->getHMenu(), controlId, commandMenuItem );
	
	// Add menu item to the parent container
	menuItemControllerContainer->addMenuItem (commandMenuItem->name(), controller);

	// Register the controller for notifications handling
	MessageDispatcher::getInstance().registerController (controller);
	
	return controller;
}

std::shared_ptr<SubMenuItemController> createSubMenuItem(std::shared_ptr<IMenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<SubMenuItem> subMenuItem) {
	// Get a new control ID for the menu item
	int controlId = createControlId();

	// First create the controller since we need an HMENU
	auto controller = std::make_shared<SubMenuItemController>( menuItemControllerContainer->getHMenu(), controlId, subMenuItem );

	// Fill MENUITEMINFO structure
	MENUITEMINFO mii = {0};
	mii.cbSize = sizeof(MENUITEMINFO);

	mii.fMask = MIIM_STRING | MIIM_ID | MIIM_FTYPE | MIIM_SUBMENU; 
    mii.fType = MFT_STRING;
	mii.wID = controlId;
    mii.dwTypeData = (LPSTR)subMenuItem->text().c_str();
	mii.cch = subMenuItem->text().size();
	mii.hSubMenu = controller->getHMenu();
	
	// Insert the new item as last item of the parent container
	int position = ::GetMenuItemCount(menuItemControllerContainer->getHMenu());
	BOOL res = ::InsertMenuItem(menuItemControllerContainer->getHMenu(), position, TRUE, &mii); 	
	
	if (!res) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}
	
	// Add menu item to the parent container
	menuItemControllerContainer->addMenuItem (subMenuItem->name(), controller);
	
	// Create children menu items
	for (auto menuItem : subMenuItem->menuItems) {
		createMenuItem (controller, menuItem.second);
	}
	
	return controller;
}

std::shared_ptr<FontResource> createFontResource(std::shared_ptr<Font> font) {
	LOGFONT logFont;
	logFont = {0};
	
	std::copy (font->fontName().begin(), font->fontName().end(), logFont.lfFaceName);
	
	HDC hDC = ::GetDC(0);
	logFont.lfHeight = -MulDiv(font->size(), ::GetDeviceCaps(hDC, LOGPIXELSY), 72);
	
	logFont.lfWeight = font->bold() ? FW_BOLD : FW_NORMAL;
	logFont.lfItalic = font->italic() ? TRUE : FALSE;
	logFont.lfUnderline = font->underline() ? TRUE : FALSE;
	
	HFONT hFont = ::CreateFontIndirect (&logFont);
	if (!hFont) {
		throw Error( "Error creating font" );
	}
	
	auto fontResource = std::make_shared<FontResource>( hFont, font );
	
	return fontResource;
}

}



#include <win/create_window.h>
#include <win/button.h>

#include "utils.h"
#include "window_controller.h"
#include "button_controller.h"
#include "menu_bar_controller.h"
#include "command_menu_item_controller.h"
#include "sub_menu_item_controller.h"
#include "message_dispatcher.h"

#include <win/command_menu_item.h>
#include <win/sub_menu_item.h>

#include <map>

namespace win {

void createButtonControl(std::shared_ptr<Button> button, HWND hWndParent);
void createMenuBarControl(std::shared_ptr<MenuBar> menuBar, std::shared_ptr<WindowController> windowController);
void createCommandMenuItem(std::shared_ptr<MenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<CommandMenuItem> commandMenuItem);
void createSubMenuItem(std::shared_ptr<MenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<SubMenuItem> subMenuItem);
	
int createControlId() {
	static int controlIdCounter = 100;
	return controlIdCounter++;
}

void createWindow(std::shared_ptr<Window> window) {
	HINSTANCE hInstance = ::GetModuleHandle(NULL);
	
	// Register class
	WNDCLASSEX wcex;

	wcex.cbSize 			= sizeof(WNDCLASSEX);
	wcex.lpfnWndProc    	= MessageDispatcher::uniqueWndProc;
	wcex.cbClsExtra     	= 0;
	wcex.cbWndExtra     	= 0;
	wcex.hInstance      	= hInstance;
	wcex.hIcon          	= ::LoadIcon (hInstance, IDI_APPLICATION);
	wcex.hCursor        	= ::LoadCursor (NULL, IDC_ARROW);
	wcex.hbrBackground  	= (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszMenuName   	= NULL;
	wcex.lpszClassName  	= window->name().c_str();
	wcex.hIconSm        	= ::LoadIcon (hInstance, IDI_APPLICATION);
	wcex.style          	= CS_HREDRAW | CS_VREDRAW;

	if (!::RegisterClassEx (&wcex)) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}	
	
	// Create window
	DWORD window_style_ex = 0;
	DWORD window_style = WS_OVERLAPPEDWINDOW;
	
	if (window->visible())
		window_style |= WS_VISIBLE;
		
	HWND hWnd = CreateWindowEx (
					window_style_ex,
	                window->name().c_str(),
	                window->title().c_str(),
	                window_style,
					window->left(),
					window->top(),
					window->width(),
					window->height(),
	                NULL,
	                NULL,
	                hInstance,
	                NULL);

	if (!hWnd) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}
	
	// Create WindowController instance
	auto controller = std::make_shared<WindowController>( hWnd, window );
	
	// Add owned controls
	for (auto control : window->controls) {
		if (control()->getType() == "Button") {
			auto buttonControl = std::dynamic_pointer_cast<Button>(control());
			if (!buttonControl) {
				throw Error( "Can not convert control to 'Button'" );
			}
			createButtonControl (buttonControl, hWnd);
		} else if (control()->getType() == "MenuBar") {
			auto menuBarControl = std::dynamic_pointer_cast<MenuBar>(control());
			if (!menuBarControl) {
				throw Error( "Can not convert control to 'MenuBar'" );
			}
			createMenuBarControl (menuBarControl, controller);
		}
	}
	
	// Register the window controller
	MessageDispatcher::getInstance().registerController (controller);
}

void createButtonControl(std::shared_ptr<Button> button, HWND hWndParent) {
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
	                hWndParent,
	                (HMENU)(intptr_t)controlId,
	                hInstance,
	                NULL);

	if (!hWnd) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}	
	
	// Create ButtonController instance
	auto controller = std::make_shared<ButtonController>( hWnd, controlId, button );
	MessageDispatcher::getInstance().registerController (controller);
	
	// Subclass window
	controller->subclass();
}

void createMenuBarControl(std::shared_ptr<MenuBar> menuBar, std::shared_ptr<WindowController> windowController) {
	auto controller = std::make_shared<MenuBarController>( menuBar );
	
	// Create children menu items	
	for (auto menuItem : menuBar->menuItems) {
		if (menuItem()->getType() == "CommandMenuItem") {
			auto commandMenuItem = std::dynamic_pointer_cast<CommandMenuItem>(menuItem());
			if (!commandMenuItem) {
				throw Error( "Can not convert control to 'CommandMenuItem'" );
			}			
			createCommandMenuItem (controller, commandMenuItem);
		} else if (menuItem()->getType() == "SubMenuItem") {
			auto subMenuItem = std::dynamic_pointer_cast<SubMenuItem>(menuItem());
			if (!subMenuItem) {
				throw Error( "Can not convert control to 'SubMenuItem'" );
			}				
			createSubMenuItem (controller, subMenuItem);
		}
	}
	
	windowController->setMenuBarController (controller);
}

void createCommandMenuItem(std::shared_ptr<MenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<CommandMenuItem> commandMenuItem) {
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
	
	// Insert the new item as last item of the parent container	
	int position = ::GetMenuItemCount(menuItemControllerContainer->getHMenu());
	BOOL res = ::InsertMenuItem(menuItemControllerContainer->getHMenu(), position, TRUE, &mii); 	
	
	if (!res) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}

	auto controller = std::make_shared<CommandMenuItemController>( menuItemControllerContainer->getHMenu(), controlId, commandMenuItem );
	
	// Add menu item to the parent container
	menuItemControllerContainer->addMenuItemController (controller);

	// Register the controller for notifications handling
	MessageDispatcher::getInstance().registerController (controller);
}

void createSubMenuItem(std::shared_ptr<MenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<SubMenuItem> subMenuItem) {
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
	menuItemControllerContainer->addMenuItemController (controller);
	
	// Create children menu items
	for (auto menuItem : subMenuItem->menuItems) {
		if (menuItem()->getType() == "CommandMenuItem") {
			auto commandMenuItem = std::dynamic_pointer_cast<CommandMenuItem>(menuItem());
			if (!commandMenuItem) {
				throw Error( "Can not convert control to 'CommandMenuItem'" );
			}			
			createCommandMenuItem (controller, commandMenuItem);
		} else if (menuItem()->getType() == "SubMenuItem") {
			auto subMenuItem = std::dynamic_pointer_cast<SubMenuItem>(menuItem());
			if (!subMenuItem) {
				throw Error( "Can not convert control to 'SubMenuItem'" );
			}				
			createSubMenuItem (controller, subMenuItem);
		}
	}	
}

int run() {
    // Main message loop:
    MSG msg;
    while (::GetMessage (&msg, NULL, 0, 0))
    {
        ::TranslateMessage (&msg);
        ::DispatchMessage (&msg);
    }

    return (int)msg.wParam;	
}

}

#include <win/create_window.h>
#include <win/button.h>

#include "utils.h"
#include "window_controller.h"
#include "button_controller.h"
#include "menu_bar_controller.h"
#include "message_dispatcher.h"

#include <map>

namespace win {

void createButtonControl(std::shared_ptr<Button> button, HWND hWndParent);
void createMenuBarControl(std::shared_ptr<MenuBar> menuBar, HWND hWndParent);
	
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
	
	for (auto control : window->controls) {
		if (control()->getType() == "Button") {
			try {
				createButtonControl (std::dynamic_pointer_cast<Button>(control()), hWnd);
			} catch (std::exception& execpt) {
				throw Error( "Can not convert control to 'Button'" );
			}
		} else if (control()->getType() == "MenuBar") {
			try {
				createMenuBarControl (std::dynamic_pointer_cast<MenuBar>(control()), hWnd);
			} catch (std::exception& execpt) {
				throw Error( "Can not convert control to 'MenuBar'" );
			}
		}
	}
	
	// Create WindowController instance
	auto controller = std::make_shared<WindowController>( hWnd, window );
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
	                (HMENU)controlId,
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

void createMenuBarControl(std::shared_ptr<MenuBar> menuBar, HWND hWndParent) {
	auto controller = std::make_shared<MenuBarController>( menuBar );
}

void createCommandMenuItem(HMENU hMenuParent, std::shared_ptr<CommanMenuItem> commandMenuItem) {
}

void createSubMenuItem(HMENU hMenuParent, std::shared_ptr<SubMenuItem> subMenuItem) {
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

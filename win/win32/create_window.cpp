#include <win/create_window.h>
#include <win/button.h>

#include "utils.h"
#include "window_controller.h"

#include <map>

namespace win {

std::map<HWND, std::shared_ptr<WindowController>> gWindowControllers;
	
void createButtonControl(std::shared_ptr<Button> button, HWND hWndParent);
	
int createControlId() {
	static int controlIdCounter = 100;
	return controlIdCounter++;
}

LRESULT CALLBACK UniqueWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
    {
		case WM_DESTROY:
			gWindowControllers.erase (hWnd);
			::PostQuitMessage(0);
			break;
		default:
			bool handled = false;
			LRESULT res = gWindowControllers[hWnd]->handleMessage (hWnd, message, wParam, lParam, handled);
			if (handled) {
				return res;
			}
			return ::DefWindowProc(hWnd, message, wParam, lParam);
			break;
    }
	
	return 0;
}
	
void createWindow(std::shared_ptr<Window> window) {
	HINSTANCE hInstance = ::GetModuleHandle(NULL);
	
	// Register class
	WNDCLASSEX wcex;

	wcex.cbSize 			= sizeof(WNDCLASSEX);
	wcex.lpfnWndProc    	= UniqueWndProc;
	wcex.cbClsExtra     	= 0;
	wcex.cbWndExtra     	= 0;
	wcex.hInstance      	= hInstance;
	wcex.hIcon          	= ::LoadIcon (hInstance, IDI_APPLICATION);
	wcex.hCursor        	= ::LoadCursor (NULL, IDC_ARROW);
	wcex.hbrBackground  	= (HBRUSH)(COLOR_WINDOW + 1);
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
		}
	}
	
	// Create WindowController instance
	auto controller = std::make_shared<WindowController>( hWnd, window );
	
	gWindowControllers.insert (std::make_pair (hWnd, controller));
}

void createButtonControl(std::shared_ptr<Button> button, HWND hWndParent) {
	HINSTANCE hInstance = ::GetModuleHandle(NULL);

	DWORD window_style_ex = 0;
	DWORD window_style = WS_TABSTOP | WS_CHILD;
	
	if (button->visible())
		window_style |= WS_VISIBLE;
	
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
	                (HMENU)createControlId(),
	                hInstance,
	                NULL);

	if (!hWnd) {
		throw Error( formatSystemMessage (::GetLastError()) );
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

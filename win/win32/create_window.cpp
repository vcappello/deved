#include <win/create_window.h>
#include <win/button.h>

#include "control_factory.h"
#include "utils.h"
#include "window_controller.h"
#include "message_dispatcher.h"

namespace win {

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
		createControl (controller, control.second);
	}
	
	// Register the window controller
	MessageDispatcher::getInstance().registerController (controller);
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

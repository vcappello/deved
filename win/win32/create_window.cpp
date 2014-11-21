#include <win/create_window.h>
#include <win/button.h>

#include "control_factory.h"
#include "utils.h"
#include "window_controller.h"
#include "message_dispatcher.h"
#include "message_loop.h"

#include <windows.h>

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
	// TODO: since the name now is not mandatory use another key!
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
	                reinterpret_cast<void*>( &window ));

	if (!hWnd) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}

	// The WindowController is created when the message WM_NCCREATE is notified
	// to the MessageDispatcher
}

int run() {
    return MessageLoop::getInstance().start();
}

std::shared_ptr<Font> getSystemFont() {
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
	
	auto font = createFont (ncm.lfMessageFont);
	
	return font;
}

}

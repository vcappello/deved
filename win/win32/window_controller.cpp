#include "window_controller.h"

#include <iostream>

namespace win {
	
WindowController::WindowController(HWND hWnd, std::shared_ptr<Window> window) :
	mHWnd( hWnd ),
	mWindow( window ) {
}

WindowController::~WindowController() {
}

LRESULT WindowController::handleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool& handled) {
	std::cout << message << std::endl; 
	handled = false;
	return 0;
}

}


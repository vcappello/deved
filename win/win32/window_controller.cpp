#include "window_controller.h"

#include <iostream>

namespace win {
	
WindowController::WindowController(HWND hWnd, std::shared_ptr<Window> window) :
	mHWnd( hWnd ),
	mWindow( window ) {
}

WindowController::~WindowController() {
}

bool WindowController::handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult) {
	std::cout << "WindowController " << message << std::endl; 
	if (message == WM_DESTROY) {
		::PostQuitMessage(0);
	}
	
	return false;
}

}


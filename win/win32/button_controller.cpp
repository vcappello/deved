#include "button_controller.h"

#include <iostream>

namespace win {
	
ButtonController::ButtonController(HWND hWnd, int commandId, std::shared_ptr<Button> button) :
	mHWnd( hWnd ),
	mCommandId( commandId ),
	mButton( button ) {
}

ButtonController::~ButtonController() {
}

bool ButtonController::handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult) {
	std::cout << "ButtonController " << message << std::endl; 
	return false;
}

void ButtonController::handleCommand(WPARAM wParam, LPARAM lParam) {
	std::cout << "ButtonController Command" << std::endl; 
}

}
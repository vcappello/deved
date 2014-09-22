#include "menu_bar_controller.h"

namespace win {
	
MenuBarController::MenuBarController(std::shared_ptr<MenuBar> menuBar) :
	mMenuBar( menuBar ) {
	mHMenu = ::CreateMenu();
}

MenuBarController::~MenuBarController() {
	// TODO: restore
	//::DestroyMenu (mHMenu);
}
	
}


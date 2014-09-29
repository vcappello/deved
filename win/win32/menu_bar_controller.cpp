#include "menu_bar_controller.h"

namespace win {
	
MenuBarController::MenuBarController(std::shared_ptr<MenuBar> menuBar) :
	mMenuBar( menuBar ) {
	mHMenu = ::CreateMenu();
		
	mMenuBar->menuItems.itemAddedEvent.add([&] (std::shared_ptr<MenuItem> menuItem) {
		createMenuItem (shared_from_this(), menuItem);
	});
	
	mMenuBar->menuItems.itemRemovedEvent.add([&] (std::shared_ptr<MenuItem> menuItem) {
		// TODO: implement this for remove item
	});		
}

MenuBarController::~MenuBarController() {
	DestroyMenu (mHMenu);
}

}


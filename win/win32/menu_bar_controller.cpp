#include "menu_bar_controller.h"

namespace win {
	
MenuBarController::MenuBarController(std::shared_ptr<MenuBar> menuBar) :
	mMenuBar( menuBar ) {
	mHMenu = ::CreateMenu();
		
	mMenuBar->menuItems.itemAddedEvent.add([&] (std::shared_ptr<MenuItem> menuItem) {
		auto controller = createMenuItemController (shared_from_this(), menuItem);
		addResource (menuItem->getName(), controller);
	});
	
	mMenuBar->menuItems.itemRemovedEvent.add([&] (std::shared_ptr<MenuItem> menuItem) {
		auto object = getResource (menuItem->getName());
		removeResource (menuItem->getName());
		object->destroy();		
	});		
}

MenuBarController::~MenuBarController() {
	::DestroyMenu (mHMenu);
}

void MenuBarController::addMenuItem(const std::string& name, std::shared_ptr<MenuItemControllerBase> menuItem) {
	addResource (name, menuItem);
}

}


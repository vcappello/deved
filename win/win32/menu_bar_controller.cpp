#include "menu_bar_controller.h"

namespace win {
	
MenuBarController::MenuBarController(std::shared_ptr<MenuBar> menuBar) :
	mMenuBar( menuBar ) {
	mHMenu = ::CreateMenu();
		
	mMenuBar->menuItems.itemAddedEvent.add([&] (std::shared_ptr<MenuItem> menuItem) {
		auto controller = createMenuItem (shared_from_this(), menuItem);
		mResources.insert (std::make_pair (menuItem->getName(), controller));
	});
	
	mMenuBar->menuItems.itemRemovedEvent.add([&] (std::shared_ptr<MenuItem> menuItem) {
		auto object = mResources[menuItem->getName()];
		mResources.erase (menuItem->getName());
		object->destroy();		
	});		
}

MenuBarController::~MenuBarController() {
	::DestroyMenu (mHMenu);
}

}


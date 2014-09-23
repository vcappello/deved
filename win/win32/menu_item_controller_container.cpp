#include "menu_item_controller_container.h"

namespace win {

MenuItemControllerContainer::MenuItemControllerContainer() {
}

MenuItemControllerContainer::~MenuItemControllerContainer() {
}

void MenuItemControllerContainer::addMenuItemController(std::shared_ptr<MenuItemControllerBase> menuItem) {
	mMenuItemControllers.push_back (menuItem);	
}
	
}


#include "sub_menu_item_controller.h"

namespace win {
	
SubMenuItemController::SubMenuItemController(HMENU hMenuParent, int commandId, std::shared_ptr<SubMenuItem> subMenuItem) :
	MenuItemControllerBase( hMenuParent, commandId ),	
	mSubMenuItem( subMenuItem ) {
		
	mHMenu = ::CreatePopupMenu();
		
	mSubMenuItem->text.changedEvent.add([&]{
		if (getText() != mSubMenuItem->text()) {
			setText (mSubMenuItem->text());
		}
	});
	
	mSubMenuItem->menuItems.itemAddedEvent.add([&] (std::shared_ptr<MenuItem> menuItem) {
		auto controller = createMenuItemController (shared_from_this(), menuItem);
		addResource (menuItem->getName(), controller);
	});
	
	mSubMenuItem->menuItems.itemRemovedEvent.add([&] (std::shared_ptr<MenuItem> menuItem) {
		auto object = getResource (menuItem->getName());
		removeResource (menuItem->getName());
		object->destroy();			
	});		
}

SubMenuItemController::~SubMenuItemController() {
	// Detach menu item from parent menu
	::RemoveMenu (mHMenuParent, mCommandId, MF_BYCOMMAND);
	// Destroy menu Handle
	::DestroyMenu (mHMenu);
}

void SubMenuItemController::addMenuItem(const std::string& name, std::shared_ptr<MenuItemControllerBase> menuItem) {
	addResource (name, menuItem);
}

}


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
		addResource (menuItem.get(), controller);
	});
	
	mSubMenuItem->menuItems.itemRemovedEvent.add([&] (std::shared_ptr<MenuItem> menuItem) {
		auto object = getResource (menuItem.get());
		removeResource (menuItem.get());
		object->destroy();			
	});		
}

SubMenuItemController::~SubMenuItemController() {
	// Detach menu item from parent menu
	::RemoveMenu (mHMenuParent, mCommandId, MF_BYCOMMAND);
	// Destroy menu Handle
	::DestroyMenu (mHMenu);
}

void SubMenuItemController::addMenuItem(std::shared_ptr<MenuItemControllerBase> menuItemController) {
	addResource (menuItemController->getMenuItem().get(), menuItemController);
}

}


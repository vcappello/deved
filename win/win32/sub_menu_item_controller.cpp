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
		createMenuItem (shared_from_this(), menuItem);
	});
	
	mSubMenuItem->menuItems.itemRemovedEvent.add([&] (std::shared_ptr<MenuItem> menuItem) {
		// TODO: implement this for remove item
	});		
}

SubMenuItemController::~SubMenuItemController() {
	::DestroyMenu (mHMenu);
}
	
}


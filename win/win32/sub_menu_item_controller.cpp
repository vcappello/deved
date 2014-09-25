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
}

SubMenuItemController::~SubMenuItemController() {
	::DestroyMenu (mHMenu);
}
	
}


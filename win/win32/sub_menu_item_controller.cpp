#include "sub_menu_item_controller.h"

namespace win {
	
SubMenuItemController::SubMenuItemController(HMENU hMenuParent, std::shared_ptr<SubMenuItem> subMenuItem) :
	mHMenuParent( hMenuParent ),
	mSubMenuItem( subMenuItem ) {
	mHMenu = ::CreatePopupMenu();
}

SubMenuItemController::~SubMenuItemController() {
	// TODO: restore
	//::DestroyMenu (mHMenu);
}
	
}


#include "sub_menu_item_controller.h"

namespace win {
	
SubMenuItemController::SubMenuItemController(HMENU hMenuParent, int commandId, std::shared_ptr<SubMenuItem> subMenuItem) :
	mHMenuParent( hMenuParent ),
	mCommandId( commandId ),	
	mSubMenuItem( subMenuItem ) {
	mHMenu = ::CreatePopupMenu();
}

SubMenuItemController::~SubMenuItemController() {
	::DestroyMenu (mHMenu);
}
	
}


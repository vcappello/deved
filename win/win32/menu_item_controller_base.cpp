#include "menu_item_controller_base.h"

namespace win {

MenuItemControllerBase::MenuItemControllerBase(HMENU hMenuParent, int commandId) :
	mHMenuParent( hMenuParent ),
	mCommandId( commandId ) {
}

MenuItemControllerBase::~MenuItemControllerBase() {
}

std::string MenuItemControllerBase::getText() {
	std::string text;
	
	MENUITEMINFO mii;
	mii.cbSize = sizeof (MENUITEMINFO);
	mii.fMask = MIIM_STRING;
	
	if (::GetMenuItemInfo (mHMenuParent, mCommandId, FALSE, &mii)) {
		text = mii.dwTypeData;
	}
	
	return text;
}

void MenuItemControllerBase::setText(const std::string& value) {
	MENUITEMINFO mii;
	mii.cbSize = sizeof (MENUITEMINFO);
	mii.fMask = MIIM_STRING;
	mii.dwTypeData = (LPSTR)value.c_str();
	mii.cch = value.size();
	
	::SetMenuItemInfo (mHMenuParent, mCommandId, FALSE, &mii);
}
		
}


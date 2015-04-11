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
	char buffer[256];
	
	MENUITEMINFO mii;
	mii = {};
	mii.cbSize = sizeof (MENUITEMINFO);
	mii.fMask = MIIM_STRING;
	mii.cch = 256; 
	mii.dwTypeData = buffer;
	
	if (!::GetMenuItemInfo (mHMenuParent, mCommandId, FALSE, &mii)) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}
	
	text = mii.dwTypeData;
	return text;
}

void MenuItemControllerBase::setText(const std::string& value) {
	MENUITEMINFO mii;
	mii = {};
	mii.cbSize = sizeof (MENUITEMINFO);
	mii.fMask = MIIM_STRING;
	mii.dwTypeData = (LPSTR)value.c_str();
	mii.cch = value.size();
	
	if (!::SetMenuItemInfo (mHMenuParent, mCommandId, FALSE, &mii)) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}
}

bool MenuItemControllerBase::isEnabled() {
	MENUITEMINFO mii;
	mii = {};
	mii.cbSize = sizeof (MENUITEMINFO);
	mii.fMask = MIIM_STATE;
	
	if (!::GetMenuItemInfo (mHMenuParent, mCommandId, FALSE, &mii)) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}
	
	return !(mii.fState & MFS_DISABLED);	
}

void MenuItemControllerBase::setEnabled(bool value) {
	MENUITEMINFO mii;
	mii = {};
	mii.cbSize = sizeof (MENUITEMINFO);
	mii.fMask = MIIM_STATE;
	mii.fState |= value ? MFS_ENABLED : MFS_DISABLED;
	
	if (!::SetMenuItemInfo (mHMenuParent, mCommandId, FALSE, &mii)) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}
}

}


/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_MENU_ITEM_CONTROLLER_BASE_H
#define WIN_WIN32_MENU_ITEM_CONTROLLER_BASE_H

#include "windows_object.h"
#include <win/menu_item.h>
#include <win/error.h>
#include "utils.h"

#include <memory>
#include <windows.h>

namespace win {

class MenuItemControllerBase : public WindowsObject {
public:
	MenuItemControllerBase(HMENU hMenuParent, int commandId);
	virtual ~MenuItemControllerBase();
	
	virtual std::shared_ptr<MenuItem> getMenuItem() = 0;

	std::string getText();
	void setText(const std::string& value);

	bool isEnabled();
	void setEnabled(bool value);

public:
	HMENU mHMenuParent;	
	int mCommandId;	
};

}

#endif // WIN_WIN32_MENU_ITEM_CONTROLLER_BASE_H


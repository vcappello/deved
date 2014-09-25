/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_COMMAND_MENU_ITEM_CONTROLLER_H
#define WIN_WIN32_COMMAND_MENU_ITEM_CONTROLLER_H

#include "i_notification_handler.h"
#include "menu_item_controller_base.h"
#include <win/command_menu_item.h>

#include <memory>
#include <windows.h>

namespace win {

class CommandMenuItemController : public INotificationHandler,
								  public MenuItemControllerBase {
public:
	CommandMenuItemController(HMENU hMenuParent, int commandId, std::shared_ptr<CommandMenuItem> commandMenuItem);
	virtual ~CommandMenuItemController();
	
	// INotificationHandler implementations
	int getCommandId() const { return mCommandId; }
	
	void handleCommand(WPARAM wParam, LPARAM lParam);
	
	// IMenuItemController implementations
	std::shared_ptr<MenuItem> getMenuItem() { return mCommandMenuItem; }
	
public:
	std::shared_ptr<CommandMenuItem> mCommandMenuItem;
};

}

#endif // WIN_WIN32_COMMAND_MENU_ITEM_CONTROLLER_H


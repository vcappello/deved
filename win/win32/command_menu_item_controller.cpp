#include "command_menu_item_controller.h"

namespace win {
	
CommandMenuItemController::CommandMenuItemController(HMENU hMenuParent, int commandId, std::shared_ptr<CommandMenuItem> commandMenuItem) :
	MenuItemControllerBase( hMenuParent, commandId ),
	mCommandMenuItem( commandMenuItem ) {
		
	mCommandMenuItem->text.changedEvent.add([&]{
		if (getText() != mCommandMenuItem->text()) {
			setText (mCommandMenuItem->text());
		}
	});

	mCommandMenuItem->enabled.changedEvent.add([&]{
		if (isEnabled() != mCommandMenuItem->enabled()) {
			setEnabled (mCommandMenuItem->enabled());
		}
	});	
}

CommandMenuItemController::~CommandMenuItemController() {
}

void CommandMenuItemController::handleCommand(WPARAM wParam, LPARAM lParam) {
	mCommandMenuItem->clickedEvent.fire();
}

void CommandMenuItemController::destroy() {
	// Detach menu item from parent menu
	::RemoveMenu (mHMenuParent, mCommandId, MF_BYCOMMAND);
	// Unregister from MessageDispatcher
	MessageDispatcher::getInstance().unregisterControllerById (mCommandId);
}

}


#include "command_menu_item_controller.h"

namespace win {
	
CommandMenuItemController::CommandMenuItemController(HMENU hMenuParent, int commandId, std::shared_ptr<CommandMenuItem> commandMenuItem) :
	mHMenuParent( hMenuParent ),
	mCommandId( commandId ),
	mCommandMenuItem( commandMenuItem ) {
}

CommandMenuItemController::~CommandMenuItemController() {
}

void CommandMenuItemController::handleCommand(WPARAM wParam, LPARAM lParam) {
}

}


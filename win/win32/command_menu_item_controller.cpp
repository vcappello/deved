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
		
}

CommandMenuItemController::~CommandMenuItemController() {
}

void CommandMenuItemController::handleCommand(WPARAM wParam, LPARAM lParam) {
}

}


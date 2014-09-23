#include "command_menu_item_controller.h"

namespace win {
	
CommandMenuItemController::CommandMenuItemController(HMENU hMenuParent, int commandId, std::shared_ptr<CommandMenuItem> commandMenuItem) :
	mHMenuParent( hMenuParent ),
	mCommandId( commandId ),
	mCommandMenuItem( commandMenuItem ) {
/*		
	mButton->text.changedEvent.add([&]{
		if (getText() != mButton->text()) {
			setText (mButton->text());
		}
	});
*/		
}

CommandMenuItemController::~CommandMenuItemController() {
}

void CommandMenuItemController::handleCommand(WPARAM wParam, LPARAM lParam) {
}

}


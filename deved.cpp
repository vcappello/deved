/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#include <memory>
#include <string>

#include <win/window.h>
#include <win/button.h>
#include <win/menu_bar.h>
#include <win/command_menu_item.h>
#include <win/sub_menu_item.h>
#include <win/create_window.h>

int main() {

	auto window = std::make_shared<win::Window>("Window1", "My window", 10, 10, 300, 200);	
	auto button1 = std::make_shared<win::Button>("Button1", "click me", 10, 10, 100, 30);
	auto button2 = std::make_shared<win::Button>("Button2", "Test", 150, 10, 100, 30);

	auto menuBar1 = std::shared_ptr<win::MenuBar>( new win::MenuBar( "MenuBar1", { 
			std::shared_ptr<win::SubMenuItem>( new win::SubMenuItem( "SubMenuItem1", "File", {
				std::make_shared<win::CommandMenuItem>( "CommandMenuItem1", "New" ),
				std::make_shared<win::CommandMenuItem>( "CommandMenuItem2", "Open" ),
				std::make_shared<win::CommandMenuItem>( "CommandMenuItem3", "Save" )
			})),
			std::shared_ptr<win::SubMenuItem>( new win::SubMenuItem( "SubMenuItem2", "Edit", { 
				std::make_shared<win::CommandMenuItem>( "CommandMenuItem4", "Cut" ),
				std::make_shared<win::CommandMenuItem>( "CommandMenuItem5", "Copy" ),
				std::make_shared<win::CommandMenuItem>( "CommandMenuItem6", "Paste" )
			}))
	}));

	window->controls = { menuBar1, button1, button2 };
	
	int counter = 0;
	button1->clickedEvent.add([&] {
		std::cout << "Ouch!" << std::endl;
		button2->visible (!button2->visible());
		button2->text ("Count:" + std::to_string (++counter));
	});
	
	win::createWindow (window);
	win::run();
	
	return 0;
}

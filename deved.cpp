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
	std::shared_ptr<win::Button> button1;
	std::shared_ptr<win::Button> button2;
	std::shared_ptr<win::CommandMenuItem> commandMenuItem3;
	std::shared_ptr<win::SubMenuItem> subMenuItem3;
	auto window = std::shared_ptr<win::Window>( new win::Window( "Window1", "My window", 10, 10, 300, 200, {
		std::shared_ptr<win::MenuBar>( new win::MenuBar( "MenuBar1", { 
				std::shared_ptr<win::SubMenuItem>( new win::SubMenuItem( "SubMenuItem1", "File", {
					std::make_shared<win::CommandMenuItem>( "CommandMenuItem1", "New" ),
					std::make_shared<win::CommandMenuItem>( "CommandMenuItem2", "Open" ),
					commandMenuItem3 = std::make_shared<win::CommandMenuItem>( "CommandMenuItem3", "Save" )
				})),
				std::shared_ptr<win::SubMenuItem>( new win::SubMenuItem( "SubMenuItem2", "Edit", { 
					std::make_shared<win::CommandMenuItem>( "CommandMenuItem4", "Cut" ),
					std::make_shared<win::CommandMenuItem>( "CommandMenuItem5", "Copy" ),
					std::make_shared<win::CommandMenuItem>( "CommandMenuItem6", "Paste" ),
					subMenuItem3 = std::make_shared<win::SubMenuItem>( "SubMenuItem3", "SubMenu" )
				}))
		})),
		button1 = std::make_shared<win::Button>("Button1", "click me", 10, 10, 100, 30),
		button2 = std::make_shared<win::Button>("Button2", "Test", 150, 10, 100, 30)
	}));
	
	int counter = 0;
	int top = 50;
	button1->clickedEvent.add([&] {
		std::cout << "Ouch!" << std::endl;
		
		button2->visible (!button2->visible());
		button2->text ("Count:" + std::to_string (++counter));
		
		commandMenuItem3->text ("Count:" + std::to_string (counter));
		commandMenuItem3->enabled (!commandMenuItem3->enabled());
		
		auto newButton = std::make_shared<win::Button>("NewButton" + std::to_string (counter), "Button " + std::to_string (counter), 150, top, 100, 30);
		window->controls.add (newButton);
		top += 40;
		
		auto newMenuItem = std::make_shared<win::CommandMenuItem>( "NewCommandMenuItem"  + std::to_string (counter), "MenuItem "  + std::to_string (counter));
		subMenuItem3->menuItems.add (newMenuItem);
	});
	
	commandMenuItem3->clickedEvent.add([&] {
		std::cout << "Hey!" << std::endl;
	});
	
	win::createWindow (window);
	win::run();
	
	return 0;
}

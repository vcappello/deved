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
	std::shared_ptr<win::Button> button3;
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
					subMenuItem3 = std::make_shared<win::SubMenuItem>( "SubMenuItem3", "Dynamic items" )
				}))
		})),
		button1 = std::make_shared<win::Button>("Button1", "Add menu item", 10, 10, 200, 30),
		button2 = std::make_shared<win::Button>("Button2", "Delete menu item", 10, 40, 200, 30),
		button3 = std::make_shared<win::Button>("Button3", "Disable menu item", 10, 70, 200, 30)
	}));

	int counter = 0;
	button1->clickedEvent.add([&] {
		counter++;
		std::string name = "NewCommandMenuItem"  + std::to_string (counter);
		auto newMenuItem = std::make_shared<win::CommandMenuItem>( 
			name, 
			"MenuItem "  + std::to_string (counter));
		subMenuItem3->menuItems.add (newMenuItem);
	});
	
	button2->clickedEvent.add([&] {
		if (counter > 0) {
			std::string name = "NewCommandMenuItem"  + std::to_string (counter);
			subMenuItem3->menuItems.remove (name);
			counter--;
		}
	});

	button3->clickedEvent.add([&] {
		if (counter > 0) {
			std::string name = "NewCommandMenuItem"  + std::to_string (counter);
			auto item = std::dynamic_pointer_cast<win::CommandMenuItem>( subMenuItem3->menuItems[name] );
			item->enabled (!item->enabled());
		}
		button1->font()->bold (!button1->font()->bold());
	});
	
	button1->font (std::make_shared<win::Font>( "CustomFont", "Comic Sans MS", 9 ));
	
	win::createWindow (window);
	win::run();
	
	return 0;
}

/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#include <memory>
#include <string>

#include <win/window.h>
#include <win/button.h>
#include <win/edit.h>
#include <win/label.h>
#include <win/group_box.h>
#include <win/list_box.h>
#include <win/text_list_item.h>
#include <win/menu_bar.h>
#include <win/command_menu_item.h>
#include <win/sub_menu_item.h>
#include <win/create_window.h>

int main() {
	std::shared_ptr<win::Button> button1;
	std::shared_ptr<win::Button> button2;
	std::shared_ptr<win::Button> button3;
	std::shared_ptr<win::Edit> edit1;
	std::shared_ptr<win::Label> label1;
	std::shared_ptr<win::CommandMenuItem> commandMenuItem3;
	std::shared_ptr<win::SubMenuItem> subMenuItem3;
	std::shared_ptr<win::TextListItem> listItem1;
	
	using children_t = std::initializer_list<std::shared_ptr<win::Control>>;
	using menu_items_t = std::initializer_list<std::shared_ptr<win::MenuItem>>;
	
	auto window = std::make_shared<win::Window>( "Window1", "My window", 10, 10, 450, 350, children_t({
		std::make_shared<win::MenuBar>( "MenuBar1", menu_items_t({ 
				std::make_shared<win::SubMenuItem>( "SubMenuItem1", "File", menu_items_t({
					std::make_shared<win::CommandMenuItem>( "CommandMenuItem1", "New" ),
					std::make_shared<win::CommandMenuItem>( "CommandMenuItem2", "Open" ),
					commandMenuItem3 = std::make_shared<win::CommandMenuItem>( "CommandMenuItem3", "Save" )
				})),
				std::make_shared<win::SubMenuItem>( "SubMenuItem2", "Edit", menu_items_t({ 
					std::make_shared<win::CommandMenuItem>( "CommandMenuItem4", "Cut" ),
					std::make_shared<win::CommandMenuItem>( "CommandMenuItem5", "Copy" ),
					std::make_shared<win::CommandMenuItem>( "CommandMenuItem6", "Paste" ),
					subMenuItem3 = std::make_shared<win::SubMenuItem>( "SubMenuItem3", "Dynamic items" )
				}))
		})),
		button1 = std::make_shared<win::Button>("Button1", "Add menu item", 10, 10, 200, 30),
		button2 = std::make_shared<win::Button>("Button2", "Delete menu item", 10, 40, 200, 30),
		button3 = std::make_shared<win::Button>("Button3", "Disable menu item", 10, 70, 200, 30),
		edit1 = std::make_shared<win::Edit>("Edit1", "Type some text", 10, 100, 200, 30),
		std::make_shared<win::GroupBox>("GroupBox1", "GroupBox", 220, 10, 200, 110, children_t({
			label1 = std::make_shared<win::Label>("Label1", "One", 10, 30, 30, 30),
			std::make_shared<win::Edit>("Edit2", "Type some text", 40, 30, 150, 30),
			std::make_shared<win::Label>("Label2", "two", 10, 70, 30, 30),
			std::make_shared<win::Edit>("Edit3", "Type some text", 40, 70, 150, 30)
		})),
		std::make_shared<win::ListBox>("ListBox1", 10, 150, 200, 100, win::ListBox::listItemsT({
			listItem1 = std::make_shared<win::TextListItem>("ListItem1", "foo"),
			std::make_shared<win::TextListItem>("ListItem2", "bar"),
		}))
	}));

	int counter = 0;
	button1->clickedEvent.add([&] {
		counter++;
		std::string name = "NewCommandMenuItem"  + std::to_string (counter);
		auto newMenuItem = std::make_shared<win::CommandMenuItem>( 
			name, 
			"MenuItem "  + std::to_string (counter));
		subMenuItem3->menuItems.add (newMenuItem);
		button2->left (button2->left() + 10);
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
		button2->enabled (!button2->enabled());
		window->defaultButton (button2);
		label1->border (!label1->border());
		listItem1->text ("foo " + std::to_string (counter));
	});
	
	button1->font (std::make_shared<win::Font>( "CustomFont", "Comic Sans MS", 9 ));
	button2->enabled (false);
	window->defaultButton (button3);
	
	win::createWindow (window);
	win::run();

	return 0;
}

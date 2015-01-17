/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

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

#include <memory>
#include <string>
#include <iostream>

int main() {

	std::shared_ptr<win::Edit> edit1;
	std::shared_ptr<win::Label> label1;
	std::shared_ptr<win::Button> button1;
	std::shared_ptr<win::ListBox> listbox1;
	std::shared_ptr<win::Button> button2;
	std::shared_ptr<win::Button> button3;
	std::shared_ptr<win::Button> button4;
	
	auto window = std::make_shared<win::Window>( "My window", 60, 10, 450, 350, win::Window::ControlsType({
		edit1 = std::make_shared<win::Edit>( "Type some text", 10, 10, 200, 30 ),
		button1 = std::make_shared<win::Button>( "Add item", 220, 10, 100, 30 ),
		button3 = std::make_shared<win::Button>( "Update item", 330, 10, 100, 30 ),		
		label1 = std::make_shared<win::Label>( "Characters: ", 10, 40, 200, 30 ),
		listbox1 = std::make_shared<win::ListBox>( 220, 50, 210, 100),
		button2 = std::make_shared<win::Button>( "Read text", 220, 160, 100, 30 ),
		button4 = std::make_shared<win::Button>( "Delete item", 330, 160, 100, 30 )
	}));

	button3->enabled (false);
	button2->enabled (false);
	button4->enabled (false);
	
	edit1->textColor (win::Color::rgb (0x00, 0x00, 0x00));
	edit1->backgroundColor (win::Color::rgb (0xff, 0xff, 0xff));
	//edit1->backgroundColor (win::Color::rgb (0x00, 0x00, 0xa9));
	
	listbox1->selectedItem.changedEvent.add([&] {
		bool enabled = true;
		if (listbox1->selectedItem() == nullptr) {
			enabled = false;
		}			
		button3->enabled (enabled);
		button2->enabled (enabled);
		button4->enabled (enabled);
	});
	
	edit1->text.changedEvent.add([&] {
		std::string message = "Characters: " + std::to_string (edit1->text().size());
		label1->text (message);
		
		if (edit1->text().size() > 5) {
			edit1->textColor (win::Color::rgb (0xff, 0xff, 0xff));
			edit1->backgroundColor (win::Color::rgb (0xd4, 0x3f, 0x3a));
			label1->textColor (win::Color::rgb (0xd4, 0x3f, 0x3a));
		} else {
			edit1->textColor (win::Color::rgb (0x00, 0x00, 0x00));
			edit1->backgroundColor (win::Color::rgb (0xff, 0xff, 0xff));
			label1->textColor (win::Color::rgb (0x00, 0x00, 0x00));
		}
	});
	
	button1->clickedEvent.add([&] {
		listbox1->listItems.add ( std::make_shared<win::TextListItem>( edit1->text() ));
	});
	
	button2->clickedEvent.add([&] {
		if (listbox1->selectedItem()) {
			auto selectedTextItem = std::dynamic_pointer_cast<win::TextListItem>( listbox1->selectedItem() );
			edit1->text (selectedTextItem->text());
		}
	});
	
	button3->clickedEvent.add([&] {
		if (listbox1->selectedItem()) {
			auto selectedTextItem = std::dynamic_pointer_cast<win::TextListItem>( listbox1->selectedItem() );
			selectedTextItem->text (edit1->text());
		}
	});
	
	button4->clickedEvent.add([&] {
		if (listbox1->selectedItem()) {
			listbox1->listItems.remove (listbox1->selectedItem());
		}
	});
	
	win::createWindow (window);
	win::run();

	return 0;
}

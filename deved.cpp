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

	auto window = std::make_shared<win::Window>("Window1");
	window->title ("My window");
	window->left (10);
	window->top (10);
	window->width (300);
	window->height (200);
	window->visible (true);
	
	auto button1 = std::make_shared<win::Button>("Button1");
	button1->text ("click me");
	button1->left (10);
	button1->top (10);
	button1->width (100);
	button1->height (30);
	button1->visible (true);

	auto button2 = std::make_shared<win::Button>("Button2");
	button2->text ("Test");
	button2->left (150);
	button2->top (10);
	button2->width (100);
	button2->height (30);
	button2->visible (true);

	auto menuBar1 = std::make_shared<win::MenuBar>("MenuBar1");

	auto subMenuItem1 = std::make_shared<win::SubMenuItem>("SubMenuItem1");
	subMenuItem1->text ("SubMenuItem1");

	auto commandMenuItem1 = std::make_shared<win::CommandMenuItem>("CommandMenuItem1");
	commandMenuItem1->text ("CommandMenuItem1");
	
	subMenuItem1->menuItems = { commandMenuItem1 };
	
	auto subMenuItem2 = std::make_shared<win::SubMenuItem>("SubMenuItem2");
	subMenuItem2->text ("SubMenuItem2");
	
	auto commandMenuItem2 = std::make_shared<win::CommandMenuItem>("CommandMenuItem2");
	commandMenuItem2->text ("CommandMenuItem2");
	
	subMenuItem2->menuItems = { commandMenuItem2 };
	
	menuBar1->menuItems = { subMenuItem1, subMenuItem2 };
	
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

/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#include <memory>
#include <string>

#include <win/window.h>
#include <win/button.h>
#include <win/create_window.h>

int main() {

	std::shared_ptr<win::Window> window = std::make_shared<win::Window>("Window1");
	window->title("My window");
	window->left(10);
	window->top(10);
	window->width(300);
	window->height(100);
	window->visible(true);
	
	std::shared_ptr<win::Button> button1 = std::make_shared<win::Button>("Button1");
	button1->text("click me");
	button1->left(10);
	button1->top(10);
	button1->width(100);
	button1->height(30);
	button1->visible(true);
	window->controls.add (button1);

	std::shared_ptr<win::Button> button2 = std::make_shared<win::Button>("Button2");
	button2->text("Test");
	button2->left(150);
	button2->top(10);
	button2->width(100);
	button2->height(30);
	button2->visible(true);
	window->controls.add (button2);

	int counter = 0;
	button1->clickedEvent.add([&] {
		std::cout << "Ouch!" << std::endl;
		button2->visible (!button2->visible());
		button2->text ("Count:" + std::to_string (counter));
	});
	
	win::createWindow (window);
	win::run();
	
	return 0;
}

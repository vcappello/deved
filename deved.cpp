/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#include <memory>

#include <win/window.h>
#include <win/button.h>
#include <win/create_window.h>

int main() {

	std::shared_ptr<win::Window> window = std::make_shared<win::Window>("Window1");
	window->title("My window");
	window->top(10);
	window->left(10);
	window->width(300);
	window->height(100);
	
	window->title.onPropertyChanged.add([&]{
		std::cout << "Title changed" << std::endl;
	});
	
	window->controls.onPropertyAdded.add([&](std::shared_ptr<win::Control> c){
		std::cout << "Control added " << c->name() << std::endl;
	});
		
	window->controls.onPropertyRemoved.add([&](std::shared_ptr<win::Control> c){
		std::cout << "Control removed " << c->name() << std::endl;
	});
	
	window->title("My window 2");
	
	std::shared_ptr<win::Button> button = std::make_shared<win::Button>("Button1");
	
	window->top(10);
	window->left(10);
	window->width(50);
	window->height(30);
	
	window->controls.add (button);

	win::createWindow (window);
	// win::runWindow (window);
	
	return 0;
}

#include <memory>
#include "win/window.h"

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
	
	window->title("My window 2");
	
	// win::runWindow (window);
	
	return 0;
}

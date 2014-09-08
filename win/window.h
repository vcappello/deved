#ifndef WIN_WINDOW_H
#define WIN_WINDOW_H

#include <win/property.h>

#include <string>
#include <utility>
#include <windows.h>

namespace win {

class Window {
public:
	explicit Window(const std::string& name) :
		name( name ) {}
	virtual ~Window() {}
		
public:
	Property<std::string> name;
	Property<std::string> title;
	Property<int> top;
	Property<int> left;
	Property<int> width;
	Property<int> height;
};

}

#endif // WIN_WINDOW_H


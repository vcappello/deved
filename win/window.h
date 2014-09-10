/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WINDOW_H
#define WIN_WINDOW_H

#include <win/property.h>
#include <win/control.h>

#include <memory>
#include <string>
#include <utility>

namespace win {

class Window {
public:
	explicit Window(const std::string& name) :
		name( name ) {
	}
	virtual ~Window() {
	}
	
	virtual std::string getType() const { return "Window"; }
	
public:
	Property<std::string> name;
	Property<std::string> title;
	Property<int> top;
	Property<int> left;
	Property<int> width;
	Property<int> height;
	Property<bool> visible;
	PropertyArray<std::shared_ptr<Control>> controls;
};

}

#endif // WIN_WINDOW_H


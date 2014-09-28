/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WINDOW_H
#define WIN_WINDOW_H

#include <win/control.h>
#include <win/property.h>

#include <memory>
#include <string>
#include <utility>

namespace win {

class Window : public Control {
public:
	explicit Window(const std::string& name) :
		Control( name ),
		visible( true ) {
	}
	Window(const std::string& name, const std::string& title, int left, int top, int width, int height) :
		Control( name ),
		title( title ),
		left( left ),
		top( top ),
		width( width ),
		height( height ),
		visible( true ) {
	}
	Window(const std::string& name, const std::string& title, int left, int top, int width, int height, std::initializer_list<std::shared_ptr<Control>> initList) :
		Control( name ),
		title( title ),
		left( left ),
		top( top ),
		width( width ),
		height( height ),
		visible( true ),
		controls( initList ) {
	}		
	virtual ~Window() {
	}
	
	// Control implementations
	virtual std::string getType() const { return "Window"; }
	
public:
	Property<std::string> title;
	Property<int> left;
	Property<int> top;
	Property<int> width;
	Property<int> height;
	Property<bool> visible;
	PropertyArray<std::shared_ptr<Control>> controls;
};

}

#endif // WIN_WINDOW_H


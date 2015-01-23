/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WINDOW_H
#define WIN_WINDOW_H

#include <win/control.h>
#include <win/property.h>
#include <win/font.h>
#include <win/button.h>
#include <win/entity_vector.h>

#include <memory>
#include <string>
#include <utility>

namespace win {

class Window : public Control {
public:
	using ControlsType = std::initializer_list<std::shared_ptr<Control>>;
	
public:
	Window(const std::string& name, const std::string& title, int left, int top, int width, int height, ControlsType initList) :
		Control( name ),
		title( title ),
		left( left ),
		top( top ),
		width( width ),
		height( height ),
		visible( true ),
		controls( initList ) {
	}		
	Window(const std::string& name, const std::string& title, int left, int top, int width, int height) :
		Window( name, title, left, top, width, height, ControlsType{ } ) {
	}
	Window(const std::string& title, int left, int top, int width, int height, ControlsType initList) :
		Window( "", title, left, top, width, height, initList ) {
	}
	Window(const std::string& title, int left, int top, int width, int height) :
		Window( title, left, top, width, height, ControlsType{ } ) {
	}
	explicit Window(const std::string& title) :
		Window( title, 0, 0, 0, 0 ) {
	}
	virtual ~Window() {
	}
	
	/** @name IEntity implementations
	 */
	///@{ 	
	virtual std::string getType() const { return "Window"; }
	///@}
	
public:
	static std::shared_ptr<Window> make(const std::string& name, const std::string& title, int left, int top, int width, int height, ControlsType initList) {
		return std::make_shared<win::Window>( name, title, left, top, width, height, initList );
	}

	static std::shared_ptr<Window> make(const std::string& name, const std::string& title, int left, int top, int width, int height) {
		return std::make_shared<win::Window>( name, title, left, top, width, height );
	}
	
	static std::shared_ptr<Window> make(const std::string& title, int left, int top, int width, int height, ControlsType initList) {
		return std::make_shared<win::Window>( title, left, top, width, height, initList );
	}

	static std::shared_ptr<Window> make(const std::string& title, int left, int top, int width, int height) {
		return std::make_shared<win::Window>( title, left, top, width, height );
	}
	
	static std::shared_ptr<Window> make(const std::string& title) {
		return std::make_shared<win::Window>( title );
	}
	
public:
	/** @name Properties
	 */
	///@{ 	
	Property<std::string> title;
	Property<int> left;
	Property<int> top;
	Property<int> width;
	Property<int> height;
	Property<bool> visible;
	Property<std::shared_ptr<Font>> font;
	Property<std::shared_ptr<Button>> defaultButton;
	EntityVector<Control> controls;
	///@}

};

}

#endif // WIN_WINDOW_H


/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_GROUP_BOX_H
#define WIN_GROUP_BOX_H
 
#include <win/control.h>
#include <win/property.h>
#include <win/font.h>
#include <win/color.h>
#include <win/entity_vector.h>

namespace win {

class GroupBox : public Control {
public:
	using ControlsType = std::initializer_list<std::shared_ptr<Control>>;

public:
	GroupBox(const std::string& name, const std::string& text, int left, int top, int width, int height, ControlsType initList) :
		Control( name ),
		text( text ),
		left( left ),
		top( top ),
		width( width ),
		height( height ),
		visible( true ),
		enabled( true ),
		controls( initList ) {
	}
	GroupBox(const std::string& name, const std::string& text, int left, int top, int width, int height) :
		GroupBox( name, text, left, top, width, height, ControlsType{ } ) {
	}	
	GroupBox(const std::string& text, int left, int top, int width, int height, ControlsType initList) :
		GroupBox( "", text, left, top, width, height, initList ) {
	}
	GroupBox(const std::string& text, int left, int top, int width, int height) :
		GroupBox( text, left, top, width, height, ControlsType{ } ) {
	}	
	explicit GroupBox(const std::string& text) :
		GroupBox( text, 0, 0, 0, 0 ) {
	}
	virtual ~GroupBox() {
	}
	
	/** @name IEntity implementations
	 */
	///@{ 
	virtual std::string getType() const { return "GroupBox"; }
	///@}
	
public:
	static std::shared_ptr<GroupBox> make(const std::string& name, const std::string& text, int left, int top, int width, int height, ControlsType initList) {
		return std::make_shared<GroupBox>( name, text, left, top, width, height, initList );
	}
	
	static std::shared_ptr<GroupBox> make(const std::string& name, const std::string& text, int left, int top, int width, int height) {
		return std::make_shared<GroupBox>( name, text, left, top, width, height );
	}	
	
	static std::shared_ptr<GroupBox> make(const std::string& text, int left, int top, int width, int height, ControlsType initList) {
		return std::make_shared<GroupBox>( text, left, top, width, height, initList );
	}
	
	static std::shared_ptr<GroupBox> make(const std::string& text, int left, int top, int width, int height) {
		return std::make_shared<GroupBox>( text, left, top, width, height );
	}
	
	static std::shared_ptr<GroupBox> make(const std::string& text) {
		return std::make_shared<GroupBox>( text );
	}
	
public:
	/** @name Properties
	 */
	///@{ 
	Property<std::string> text;
	Property<int> left;
	Property<int> top;
	Property<int> width;
	Property<int> height;	
	Property<bool> visible;
	Property<bool> enabled;
	Property<std::shared_ptr<Color>> textColor;
	Property<std::shared_ptr<Color>> backgroundColor;
	Property<std::shared_ptr<Font>> font;
	EntityVector<Control> controls;
	///@}
};

}
 
#endif //  WIN_GROUP_BOX_H
 
 
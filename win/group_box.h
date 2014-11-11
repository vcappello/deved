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
#include <win/entity_map.h>

namespace win {

class GroupBox : public Control {
public:
	// TODO: use delegating constructor
	explicit GroupBox(const std::string& name) :
		Control( name ),
		visible( true ),
		enabled( true ) {
	}
	GroupBox(const std::string& name, const std::string& text, int left, int top, int width, int height) :
		Control( name ),
		text( text ),
		left( left ),
		top( top ),
		width( width ),
		height( height ),
		visible( true ),
		enabled( true ) {
	}
	GroupBox(const std::string& name, const std::string& text, int left, int top, int width, int height, std::initializer_list<std::shared_ptr<Control>> initList) :
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
	virtual ~GroupBox() {
	}
	
	/** @name IEntity implementations
	 */
	///@{ 
	virtual std::string getType() const { return "GroupBox"; }
	///@}
	
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
	Property<std::shared_ptr<Font>> font;
	EntityMap<Control> controls;
	///@}
};

}
 
#endif //  WIN_GROUP_BOX_H
 
 
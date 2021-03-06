/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_EDIT_H
#define WIN_EDIT_H
 
#include <win/control.h>
#include <win/property.h>
#include <win/font.h>
#include <win/color.h>

namespace win {

class Edit : public Control {
public:
	Edit(const std::string& name, const std::string& text, int left, int top, int width, int height) :
		Control( name ),
		text( text ),
		left( left ),
		top( top ),
		width( width ),
		height( height ),
		visible( true ),
		enabled( true ),
		multiline( false ),
		border( true ) {
	}
	Edit(const std::string& text, int left, int top, int width, int height) :
		Edit( "", text, left, top, width, height ) {
	}	
	explicit Edit(const std::string& text) :
		Edit( text, 0, 0, 0, 0 ) {
	}	
	virtual ~Edit() {
	}
	
	/** @name IEntity implementations
	 */
	///@{ 
	virtual std::string getType() const { return "Edit"; }
	///@}

public:
	static std::shared_ptr<Edit> make(const std::string& name, const std::string& text, int left, int top, int width, int height) {
		return std::make_shared<Edit>( name, text, left, top, width, height );
	}
	static std::shared_ptr<Edit> make(const std::string& text, int left, int top, int width, int height) {
		return std::make_shared<Edit>( text, left, top, width, height );
	}	
	static std::shared_ptr<Edit> make(const std::string& text) {
		return std::make_shared<Edit>( text );
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
	Property<bool> multiline;
	Property<bool> border;
	Property<std::shared_ptr<Color>> textColor;
	Property<std::shared_ptr<Color>> backgroundColor;
	Property<std::shared_ptr<Font>> font;
	///@}
};

}
 
#endif //  WIN_EDIT_H
 
 
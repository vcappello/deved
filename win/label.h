/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_LABEL_H
#define WIN_LABEL_H
 
#include <win/control.h>
#include <win/property.h>
#include <win/font.h>
#include <win/color.h>

namespace win {

class Label : public Control {
public:
	Label(const std::string& name, const std::string& text, int left, int top, int width, int height) :
		Control( name ),
		text( text ),
		left( left ),
		top( top ),
		width( width ),
		height( height ),
		visible( true ),
		enabled( true ),
		border( false ) {
	}
	Label(const std::string& text, int left, int top, int width, int height) :
		Label( "", text, left, top, width, height ) {
	}		
	explicit Label(const std::string& text) :
		Label( text, 0, 0, 0, 0 ) {
	}	
	virtual ~Label() {
	}
	
	/** @name IEntity implementations
	 */
	///@{ 
	virtual std::string getType() const { return "Label"; }
	///@}
	
public:
	static std::shared_ptr<Label> make(const std::string& name, const std::string& text, int left, int top, int width, int height) {
		return std::make_shared<Label>( name, text, left, top, width, height );
	}
	
	static std::shared_ptr<Label> make(const std::string& text, int left, int top, int width, int height) {
		return std::make_shared<Label>( text, left, top, width, height );
	}
	
	static std::shared_ptr<Label> make(const std::string& text) {
		return std::make_shared<Label>( text );
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
	Property<bool> border;
	Property<std::shared_ptr<Color>> textColor;
	Property<std::shared_ptr<Color>> backgroundColor;
	Property<std::shared_ptr<Font>> font;
	///@}
};

}
 
#endif //  WIN_LABEL_H
 
 
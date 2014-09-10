/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */
 
 #include <win/control.h>
 #include <win/property.h>
 
 #ifndef WIN_BUTTON_H
 #define WIN_BUTTON_H
 
namespace win {

class Button : public Control {
public:
	explicit Button(const std::string& name) :
		Control( name ) {
	}
	virtual ~Button() {
	}
	
	virtual std::string getType() const { return "Button"; }
	
public:
	Property<std::string> text;
};

}
 
 #endif //  WIN_BUTTON_H
 
 
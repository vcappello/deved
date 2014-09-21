/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */
 
#ifndef WIN_MENU_H
#define WIN_MENU_H
 
#include <win/control.h>
#include <win/property.h>
#include <win/menu_item.h>

#include <string>
#include <memory>

namespace win {

class Menu : public Control {
public:
	explicit Menu(const std::string& name) :
		Control( name ) {
	}
	virtual ~Menu() {
	}
	
	// Control implementations	
	virtual std::string getType() const { return "Menu"; }
	
public:
	Property<std::string> text;
	PropertyArray<std::shared_ptr<MenuItem>> menuItems;
};

}
 
#endif //  WIN_MENU_H
 
 
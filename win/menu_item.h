/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */
 
#ifndef WIN_MENU_ITEM_H
#define WIN_MENU_ITEM_H

#include <win/control.h>
#include <win/property.h>

#include <string>

namespace win {

class MenuItem : public Control {
public:
	explicit MenuItem(const std::string& name) :
		Control( name ) {
	}
	virtual ~MenuItem() {
	}
	
	// Control implementations	
	// virtual std::string getType() const { return "Menu"; } // Not implemented
	
public:
};

}
 
#endif // WIN_MENU_ITEM_H
 
 
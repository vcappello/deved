/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */
 
#ifndef WIN_MENU_BAR_H
#define WIN_MENU_BAR_H

#include <win/control.h>
#include <win/property.h>
#include <win/menu_item.h>

#include <memory>

namespace win {

class MenuBar : public Control {
public:
	explicit MenuBar(const std::string& name) :
		Control( name ) {
	}
	MenuBar(const std::string& name, std::initializer_list<std::shared_ptr<MenuItem>> initList) :
		Control( name ),
		menuItems( initList ) {
		
	}	
	virtual ~MenuBar() {
	}
	
	// Control implementations	
	virtual std::string getType() const { return "MenuBar"; }
	
public:
	PropertyArray<std::shared_ptr<MenuItem>> menuItems;
};

}
 
#endif //  WIN_MENU_BAR_H
 
 
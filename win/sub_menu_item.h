/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */
 
#ifndef WIN_SUB_MENU_ITEM_H
#define WIN_SUB_MENU_ITEM_H

#include <win/menu_item.h>

#include <memory>

namespace win {

class SubMenuItem : public MenuItem {
public:
	explicit SubMenuItem(const std::string& name) :
		MenuItem( name ) {
	}
	virtual ~SubMenuItem() {
	}
	
	// Control implementations	
	virtual std::string getType() const { return "SubMenuItem"; } 
	
public:
	Property<std::string> text;	
	PropertyArray<std::shared_ptr<MenuItem>> menuItems;	
};

}
 
#endif // WIN_SUB_MENU_ITEM_H
 
 
/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */
 
#ifndef WIN_SUB_MENU_ITEM_H
#define WIN_SUB_MENU_ITEM_H

#include <win/menu_item.h>
#include <win/entity_map.h>

#include <memory>

namespace win {

class SubMenuItem : public MenuItem {
public:
	// TODO: use delegating constructor
	explicit SubMenuItem(const std::string& name) :
		MenuItem( name ) {
	}
	SubMenuItem(const std::string& name, std::initializer_list<std::shared_ptr<MenuItem>> initList) :
		MenuItem( name ),
		menuItems( initList ) {
	}	
	SubMenuItem(const std::string& name, const std::string& text) :
		MenuItem( name ),
		text( text ) {
	}
	SubMenuItem(const std::string& name, const std::string& text, std::initializer_list<std::shared_ptr<MenuItem>> initList) :
		MenuItem( name ),
		text( text ),
		menuItems( initList ) {
	}	
	virtual ~SubMenuItem() {
	}
	
	/** @name Entity implementations
	 */
	///@{ 
	virtual std::string getType() const { return "SubMenuItem"; } 
	///@}
	
public:
	/** @name Properties
	 */
	///@{
	Property<std::string> text;	
	EntityMap<MenuItem> menuItems;	
	///@}
};

}
 
#endif // WIN_SUB_MENU_ITEM_H
 
 
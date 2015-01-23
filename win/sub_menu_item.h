/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */
 
#ifndef WIN_SUB_MENU_ITEM_H
#define WIN_SUB_MENU_ITEM_H

#include <win/menu_item.h>
#include <win/entity_vector.h>

#include <memory>

namespace win {

class SubMenuItem : public MenuItem {
public:
	using MenuItemsType = std::initializer_list<std::shared_ptr<win::MenuItem>>;

public:
	SubMenuItem(const std::string& name, const std::string& text, MenuItemsType initList) :
		MenuItem( name ),
		text( text ),
		menuItems( initList ) {
	}
	SubMenuItem(const std::string& text, MenuItemsType initList) :
		SubMenuItem( "", text, initList ) {
	}
	explicit SubMenuItem(const std::string& text) :
		SubMenuItem( text, MenuItemsType{ } ) {
	}
	virtual ~SubMenuItem() {
	}
	
	/** @name Entity implementations
	 */
	///@{ 
	virtual std::string getType() const { return "SubMenuItem"; } 
	///@}
	
public:
	static std::shared_ptr<SubMenuItem> make(const std::string& name, const std::string& text, MenuItemsType initList) {
		return std::make_shared<SubMenuItem>( name, text, initList );
	}
	
	static std::shared_ptr<SubMenuItem> make(const std::string& text, MenuItemsType initList) {
		return std::make_shared<SubMenuItem>( text, initList );
	}
	
	static std::shared_ptr<SubMenuItem> make(const std::string& text) {
		return std::make_shared<SubMenuItem>( text );
	}
	
public:
	/** @name Properties
	 */
	///@{
	Property<std::string> text;	
	EntityVector<MenuItem> menuItems;	
	///@}
};

}
 
#endif // WIN_SUB_MENU_ITEM_H
 
 
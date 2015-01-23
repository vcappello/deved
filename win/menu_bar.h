/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */
 
#ifndef WIN_MENU_BAR_H
#define WIN_MENU_BAR_H

#include <win/control.h>
#include <win/property.h>
#include <win/entity_vector.h>
#include <win/menu_item.h>

#include <memory>

namespace win {

class MenuBar : public Control {
public:
	using MenuItemsType = std::initializer_list<std::shared_ptr<win::MenuItem>>;

public:
	MenuBar(const std::string& name, MenuItemsType initList) :
		Control( name ),
		menuItems( initList ) {
		
	}
	MenuBar(MenuItemsType initList) :
		MenuBar( "", initList ) {
		
	}
	explicit MenuBar() :
		MenuBar( MenuItemsType{ } ) {
	}
	virtual ~MenuBar() {
	}
	
	/** @name IEntity implementations
	 */
	///@{ 	
	virtual std::string getType() const { return "MenuBar"; }
	///@}
	
public:
	static std::shared_ptr<MenuBar> make(const std::string& name, MenuItemsType initList) {
		return std::make_shared<MenuBar>( name, initList );
	}
	
	static std::shared_ptr<MenuBar> make(MenuItemsType initList) {
		return std::make_shared<MenuBar>( initList );		
	}
	
	static std::shared_ptr<MenuBar> make() {
		return std::make_shared<MenuBar>();		
	}
	
public:
	/** @name Properties
	 */
	///@{ 	
	EntityVector<MenuItem> menuItems;
	///@}
};

}
 
#endif //  WIN_MENU_BAR_H
 
 
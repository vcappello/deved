/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */
 
#ifndef WIN_MENU_ITEM_H
#define WIN_MENU_ITEM_H

#include <win/entity.h>
#include <win/property.h>

#include <string>

namespace win {

class MenuItem : public Entity {
public:
	explicit MenuItem(const std::string& name) :
		name( name ) {
	}
	virtual ~MenuItem() {
	}
	
	/** @name Entity implementations
	 */
	///@{
	virtual std::string getName() const { return name(); }
	
	// virtual std::string getType() const { return "Menu"; } // Not implemented
	///@}
	
public:
	/** @name Properties
	 */
	///@{
	Property<std::string> name;	
	///@}
};

}
 
#endif // WIN_MENU_ITEM_H
 
 
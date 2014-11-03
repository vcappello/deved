/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_LIST_ITEM_H
#define WIN_LIST_ITEM_H

#include <win/property.h>
#include <win/i_entity.h>

#include <string>

namespace win {
	
/**
 * Base class for ListBox item entities
 */
class ListItem : public IEntity {
public:
	explicit ListItem(const std::string& name) :
		name( name ) {
	}
	virtual ~ListItem() {
	}
	
	/** @name IEntity implementations
	 */
	///@{ 	
	virtual std::string getName() const { return name(); }
	
	// virtual std::string getType() const = 0; // Not implemented
	///@}
	
public:
	/** @name Properties
	 */
	///@{ 	
	Property<std::string> name;
	///@}

	/** @name Events
	 */
	///@{ 
	///@}
};

}

#endif // WIN_LIST_ITEM_H


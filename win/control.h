/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_CONTROL_H
#define WIN_CONTROL_H

#include <win/property.h>
#include <win/i_entity.h>

#include <string>

namespace win {
	
/**
 * Base class for all control entities
 */
class Control : public IEntity {
public:
	Control() {
	}
	explicit Control(const std::string& name) :
		name( name ) {
	}
	virtual ~Control() {
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
};

}

#endif // WIN_CONTROL_H


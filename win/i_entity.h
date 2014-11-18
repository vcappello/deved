/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_I_ENTITY_H
#define WIN_I_ENTITY_H

#include <string>

namespace win {

/**
 * Interface for model entities
 */
class IEntity {
public:
	using InstanceIdType = IEntity*;

public:
	virtual ~IEntity() {
	}
	
	virtual std::string getType() const = 0;
	
	virtual std::string getName() const = 0;
	
public:
};

}

#endif // WIN_I_ENTITY_H


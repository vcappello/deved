/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_CONTROL_H
#define WIN_CONTROL_H

#include <win/property.h>

#include <string>

namespace win {
	
/**
 * Base class for all controls
 */
class Control {
public:
	explicit Control(const std::string& name) :
		name( name ) {
	}
	virtual ~Control() {
	}
	
	virtual std::string getType() const = 0;

public:
	Property<std::string> name;
};

}

#endif // WIN_CONTROL_H


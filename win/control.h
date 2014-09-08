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
	
class Control {
public:
	explicit Control(const std::string& name) :
		name( name ) {
	}
	virtual ~Control() {
	}
	
public:
	Property<std::string> name;
	Property<int> top;
	Property<int> left;
	Property<int> width;
	Property<int> height;	
};

}

#endif // WIN_CONTROL_H


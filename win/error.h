/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_ERROR_H
#define WIN_ERROR_H

#include <stdexcept>
#include <string>

namespace win {

class Error : public std::runtime_error {
public:
	explicit Error(const std::string& msg) :
		std::runtime_error( msg ) {
	}
	virtual ~Error() throw() {
	}
		
public:
};

}

#endif // WIN_ERROR_H


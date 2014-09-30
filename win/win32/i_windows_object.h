/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_WINDOWS_OBJECT_H
#define WIN_WIN32_WINDOWS_OBJECT_H

namespace win {

class IWindowsObject {
public:
	IWindowsObject() {
	}
	virtual ~IWindowsObject() {
	}

	virtual void destroy() = 0;

};

}

#endif // WIN_WIN32_WINDOWS_OBJECT_H

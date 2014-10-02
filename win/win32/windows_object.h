/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_WINDOWS_OBJECT_H
#define WIN_WIN32_WINDOWS_OBJECT_H

#include <map>
#include <string>
#include <memory>

namespace win {

class WindowsObject {
public:
	WindowsObject();
	virtual ~WindowsObject();
	
	virtual void addResource(const std::string& name, std::shared_ptr<WindowsObject> object);

	virtual void destroy();

protected:
	std::map<std::string, std::shared_ptr<WindowsObject>> mResources;
};

}

#endif // WIN_WIN32_WINDOWS_OBJECT_H

/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_WINDOWS_OBJECT_H
#define WIN_WIN32_WINDOWS_OBJECT_H

#include <win/i_entity.h>

#include <map>
#include <string>
#include <memory>

namespace win {

class WindowsObject {
public:
	using InstanceIdType = IEntity*;

public:
	WindowsObject();
	virtual ~WindowsObject();
	
	virtual void destroy();

protected:
	std::map<InstanceIdType, std::shared_ptr<WindowsObject>> mResources;

protected:
	virtual void addResource(const InstanceIdType& id, std::shared_ptr<WindowsObject> object);
	virtual void removeResource(const InstanceIdType& id);
	virtual bool resourceExist(const InstanceIdType& id) const;

	virtual std::shared_ptr<WindowsObject> getResource(const InstanceIdType& id);
	virtual std::shared_ptr<WindowsObject> getResource(const InstanceIdType& id) const;

	virtual std::shared_ptr<WindowsObject> findResourceById(const InstanceIdType& id);
};

}

#endif // WIN_WIN32_WINDOWS_OBJECT_H

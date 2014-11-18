#include "windows_object.h"

namespace win {
	
WindowsObject::WindowsObject() {
}

WindowsObject::~WindowsObject() {
}

void WindowsObject::addResource(const InstanceIdType& id, std::shared_ptr<WindowsObject> object) {
	mResources.insert (std::make_pair( id, object ));
}

void WindowsObject::removeResource(const InstanceIdType& id) {
	mResources.erase (id);
}

bool WindowsObject::resourceExist(const InstanceIdType& id) const {
	return mResources.find (id) != mResources.end();
}

std::shared_ptr<WindowsObject> WindowsObject::getResource(const InstanceIdType& id) {
	return mResources.at (id);
}

std::shared_ptr<WindowsObject> WindowsObject::getResource(const InstanceIdType& id) const {
	return mResources.at (id);
}

std::shared_ptr<WindowsObject> WindowsObject::findResourceById(const InstanceIdType& id) {
	return getResource (id);
}

void WindowsObject::destroy() {
	// Destroy all resources
	for (auto obj : mResources) {
		obj.second->destroy();
	};	
}
	
}


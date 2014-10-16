#include "windows_object.h"

namespace win {
	
WindowsObject::WindowsObject() {
}

WindowsObject::~WindowsObject() {
}

void WindowsObject::addResource(const std::string& name, std::shared_ptr<WindowsObject> object) {
	mResources.insert (std::make_pair( name, object ));
}

void WindowsObject::removeResource(const std::string& name) {
	mResources.erase (name);
}

bool WindowsObject::resourceExist(const std::string& name) const {
	return mResources.find (name) != mResources.end();
}

std::shared_ptr<WindowsObject> WindowsObject::getResource(const std::string& name) {
	return mResources.at(name);
}

std::shared_ptr<WindowsObject> WindowsObject::getResource(const std::string& name) const {
	return mResources.at(name);
}

std::shared_ptr<WindowsObject> WindowsObject::findResourceByName(const std::string& name) {
	return getResource (name);
}

void WindowsObject::destroy() {
	// Destroy all resources
	for (auto obj : mResources) {
		obj.second->destroy();
	};	
}
	
}


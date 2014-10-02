#include "windows_object.h"

namespace win {
	
WindowsObject::WindowsObject() {
}
WindowsObject::~WindowsObject() {
}

void WindowsObject::addResource(const std::string& name, std::shared_ptr<WindowsObject> object) {
	mResources.insert (std::make_pair( name, object ));
}

void WindowsObject::destroy() {
	// Destroy all children
	for (auto obj : mResources) {
		obj.second->destroy();
	};	
}
	
}


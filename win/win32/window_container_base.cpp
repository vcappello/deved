#include "window_container_base.h"

namespace win {
	
WindowContainerBase::WindowContainerBase(HWND hWnd) :
	WindowBase( hWnd ) {
}

WindowContainerBase::~WindowContainerBase() {
}

void WindowContainerBase::addChildWindow(const WindowsObject::InstanceIdType& id, std::shared_ptr<WindowBase> child) {
	addResource (id, child);
}

}


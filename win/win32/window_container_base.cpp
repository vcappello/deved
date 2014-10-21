#include "window_container_base.h"

namespace win {
	
WindowContainerBase::WindowContainerBase(HWND hWnd) :
	WindowBase( hWnd ) {
}

WindowContainerBase::~WindowContainerBase() {
}
	
void WindowContainerBase::addChildWindow(const std::string& name, std::shared_ptr<WindowBase> child) {
	addResource (name, child);
}

}


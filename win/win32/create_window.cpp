#include "create_window.h"

namespace win {
	
std::shared_ptr<WindowController> createWindow(std::shared_ptr<Window> window) {
	return std::make_shared<WindowController>();
}
	
}

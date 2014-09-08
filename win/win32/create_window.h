/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN32_WIN_CREATE_WINDOW_H
#define WIN32_WIN_CREATE_WINDOW_H

#include <win/window.h>
#include <win/window_controller.h>

#include <memory>

namespace win {
	
std::shared_ptr<WindowController> createWindow(std::shared_ptr<Window> window);
	
}

#endif // WIN32_WIN_CREATE_WINDOW_H



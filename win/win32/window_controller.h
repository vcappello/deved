/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_WINDOW_CONTROLLER_H
#define WIN_WIN32_WINDOW_CONTROLLER_H

#include <win/window.h>

#include <memory>
#include <windows.h>

namespace win {

class WindowController {
public:
	explicit WindowController(HWND hWnd, std::shared_ptr<Window> window);
	virtual ~WindowController();
	
	LRESULT handleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool& handled);

protected:
	HWND mHWnd;
	std::shared_ptr<Window> mWindow;
};

}

#endif // WIN_WIN32_WINDOW_CONTROLLER_H

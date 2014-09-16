/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_WINDOW_CONTROLLER_H
#define WIN_WIN32_WINDOW_CONTROLLER_H

#include <win/window.h>
#include "window_base.h"

#include <memory>
#include <windows.h>

namespace win {

class WindowController : public WindowBase {
public:
	explicit WindowController(HWND hWnd, std::shared_ptr<Window> window);
	virtual ~WindowController();

public:
	std::shared_ptr<Window> getWindow() { return mWindow; }

	// IMessageable implementations
	HWND getHWnd() { return mHWnd; }
	
	bool handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult);

protected:
	std::shared_ptr<Window> mWindow;
};

}

#endif // WIN_WIN32_WINDOW_CONTROLLER_H

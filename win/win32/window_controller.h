/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_WINDOW_CONTROLLER_H
#define WIN_WIN32_WINDOW_CONTROLLER_H

#include <win/window.h>
#include "i_messageable.h"

#include <memory>
#include <windows.h>

namespace win {

class WindowController : public IMessageable {
public:
	explicit WindowController(HWND hWnd, std::shared_ptr<Window> window);
	virtual ~WindowController();

	std::shared_ptr<Window> getWindow() { return mWindow; }

	// IMessageable implementations
	HWND getHWnd() { return mHWnd; }
	
	bool handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult);

protected:
	HWND mHWnd;
	std::shared_ptr<Window> mWindow;
};

}

#endif // WIN_WIN32_WINDOW_CONTROLLER_H

/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_WINDOW_CONTROLLER_H
#define WIN_WIN32_WINDOW_CONTROLLER_H

#include <win/window.h>
#include "window_base.h"
#include "menu_bar_controller.h"
#include "control_factory.h"

#include <memory>
#include <windows.h>

namespace win {

class WindowController : public WindowBase,
                         public std::enable_shared_from_this<WindowController> {
public:
	explicit WindowController(HWND hWnd, std::shared_ptr<Window> window);
	virtual ~WindowController();

public:
	std::shared_ptr<Window> getWindow() { return mWindow; }

	void setMenuBarController(std::shared_ptr<MenuBarController> menuBarController);
	
	// IMessageHandler implementations from WindowBase
	// HWND getHWnd() { return mHWnd; } // Implemented on WindowBase
	
	bool handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult);

	LRESULT callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	// Override WindowBase
	Point getPosition();
	
protected:
	std::shared_ptr<Window> mWindow;
	std::shared_ptr<MenuBarController> mMenuBarController;
};

}

#endif // WIN_WIN32_WINDOW_CONTROLLER_H

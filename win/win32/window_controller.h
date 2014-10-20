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
#include "message_loop.h"
#include "window_layout.h"

#include <memory>
#include <map>
#include <string>
#include <windows.h>

namespace win {

class WindowController : public WindowBase,
                         public std::enable_shared_from_this<WindowController> {
public:
	WindowController(HWND hWnd, std::shared_ptr<Window> window);
	virtual ~WindowController();

public:
	std::shared_ptr<Window> getWindow() { return mWindow; }

	void setMenuBarController(std::shared_ptr<MenuBarController> menuBarController);
	void addChildWindow(const std::string& name, std::shared_ptr<WindowBase> child);
	
	int getDefaultButtonId() const;
	
	void updateDefaultButton();
	
	/** @name IMessageHandler implementations
	 */
	///@{ 
	// HWND getHWnd() { return mHWnd; } // Implemented on WindowBase
	
	bool handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult);

	LRESULT callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	///@}
	
protected:
	std::shared_ptr<Window> mWindow;
	std::shared_ptr<MenuBarController> mMenuBarController;
	WindowLayout<Window> mLayout;
	int mDefaultId;

};

}

#endif // WIN_WIN32_WINDOW_CONTROLLER_H

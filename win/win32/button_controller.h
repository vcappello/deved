/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_BUTTON_CONTROLLER_H
#define WIN_WIN32_BUTTON_CONTROLLER_H

#include <win/button.h>
#include "window_base.h"
#include "i_notification_handler.h"

#include <memory>
#include <windows.h>

namespace win {

class ButtonController : public WindowBase, 
                         public INotificationHandler {
public:
	explicit ButtonController(HWND hWnd, int commandId, std::shared_ptr<Button> button);
	virtual ~ButtonController();

	std::shared_ptr<Button> getButton() { return mButton; }

	void subclass();
	
	// IMessageHandler implementations
	// HWND getHWnd() { return mHWnd; } // Implemented on WindowBase
	
	bool handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult);

	LRESULT callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	// INotificationHandler implementations
	int getCommandId() const { return mCommandId; }
	
	void handleCommand(WPARAM wParam, LPARAM lParam);
	
protected:
	int mCommandId;
	std::shared_ptr<Button> mButton;
	WNDPROC mOldWndProc;
};

}

#endif // WIN_WIN32_BUTTON_CONTROLLER_H

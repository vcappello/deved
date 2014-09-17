/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_BUTTON_CONTROLLER_H
#define WIN_WIN32_BUTTON_CONTROLLER_H

#include <win/button.h>
#include "i_message_handler.h"
#include "i_notification_handler.h"

#include <memory>
#include <windows.h>

namespace win {

class ButtonController : public IMessageHandler, public INotificationHandler {
public:
	explicit ButtonController(HWND hWnd, int commandId, std::shared_ptr<Button> button);
	virtual ~ButtonController();

	std::shared_ptr<Button> getButton() { return mButton; }

	// IMessageable implementations
	HWND getHWnd() { return mHWnd; }
	
	bool handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult);

	// ICommandable implementations
	int getCommandId() const { return mCommandId; }
	
	void handleCommand(WPARAM wParam, LPARAM lParam);
	
protected:
	HWND mHWnd;
	int mCommandId;
	std::shared_ptr<Button> mButton;
};

}

#endif // WIN_WIN32_BUTTON_CONTROLLER_H

/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_MESSAGE_DISPATCHER_H
#define WIN_WIN32_MESSAGE_DISPATCHER_H

#include <win/window.h>
#include "i_message_handler.h"
#include "i_notification_handler.h"

#include <memory>
#include <map>
#include <windows.h>

namespace win {

/**
 * Send messages and notifications to the recipient controller
 */
class MessageDispatcher {
private:
	MessageDispatcher();
	MessageDispatcher(const MessageDispatcher&);
	void operator=(const MessageDispatcher&);

public:
	virtual ~MessageDispatcher();
	
	static MessageDispatcher& getInstance();

	static LRESULT CALLBACK uniqueWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	template<class T>
	void registerController(std::shared_ptr<T> controller) {
		std::shared_ptr<IMessageHandler> messageHandler = std::dynamic_pointer_cast<IMessageHandler>(controller);
		if (messageHandler) {
			mMessageHandlers.insert (std::make_pair (messageHandler->getHWnd(), messageHandler));
		}
		
		std::shared_ptr<INotificationHandler> notificationHandler = std::dynamic_pointer_cast<INotificationHandler>(controller);
		if (notificationHandler) {
			mNotificationHandlers.insert (std::make_pair (notificationHandler->getCommandId(), notificationHandler));
		}		
	}
	
	void unregisterControllerByHandle(HWND hWnd);
	
	void unregisterControllerById(int id);
	
	LRESULT dispatchMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	LRESULT dispatchCommand(WPARAM wParam, LPARAM lParam);

private:
	std::map<HWND, std::shared_ptr<IMessageHandler>> mMessageHandlers;
	std::map<int, std::shared_ptr<INotificationHandler>> mNotificationHandlers;
};

}

#endif // WIN_WIN32_MESSAGE_DISPATCHER_H

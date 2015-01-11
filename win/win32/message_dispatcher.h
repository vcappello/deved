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
	
	/**
	 * Return the message dispacher object
	 * @return the message dispatcher object
	 */
	static MessageDispatcher& getInstance();

	/**
	 * The window procedure associated to all windows created by the win framework.
	 * The system call this window procedure when a new message need to be processed.
	 * The message is notified to the recipient controller.
	 * 
	 * @param hWnd A handle to the window.
	 * @param message The message
	 * @param wParam Additional message information
	 * @param lParam Additional message information
	 * @return The return value is the result of the message processing and depends on the message sent
	 */
	static LRESULT CALLBACK uniqueWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/**
	 * Register a new controller for handle messages or notifications. When the controller
	 * is registered it can receive messages and/or notifications from the uniqueWndProc
	 * 
	 * @param controller The controller must implement IMessageHandler and/or INotificationHandler
	 */
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
	
	/**
	 * Unregister a controller by window handle
	 * 
	 * @param hWnd the window handle
	 */
	void unregisterControllerByHandle(HWND hWnd);
	
	/**
	 * Unregister a controller by command id
	 * 
	 * @param id the command id
	 */
	void unregisterControllerById(int id);
	
	std::shared_ptr<IMessageHandler> getControllerByHandle(HWND hWnd);

	std::shared_ptr<INotificationHandler> getControllerById(int id);
	
protected:
	std::map<HWND, std::shared_ptr<IMessageHandler>> mMessageHandlers;
	std::map<int, std::shared_ptr<INotificationHandler>> mNotificationHandlers;

protected:
	LRESULT dispatchMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	LRESULT dispatchCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	LRESULT dispatchCtlColor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

}

#endif // WIN_WIN32_MESSAGE_DISPATCHER_H

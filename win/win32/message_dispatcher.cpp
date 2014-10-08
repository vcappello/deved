#include "message_dispatcher.h"

#include "window_controller.h"
#include "message_dispatcher.h"

namespace win {
	
MessageDispatcher::MessageDispatcher() {
}

MessageDispatcher::~MessageDispatcher() {
}

MessageDispatcher& MessageDispatcher::getInstance() {
	static MessageDispatcher instance;
	
	return instance;
}

LRESULT CALLBACK MessageDispatcher::uniqueWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (message)
    {
		case WM_NCCREATE:
		{
			if (reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams != 0) {
				auto window = reinterpret_cast<std::shared_ptr<Window>*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
				auto controller = createWindowController (hWnd, *window);
			}
			result = getInstance().dispatchMessage (hWnd, message, wParam, lParam);
			break;
		}
		case WM_COMMAND:
		{
			getInstance().dispatchMessage (hWnd, message, wParam, lParam);
			result = getInstance().dispatchCommand (wParam, lParam);
			break;
		}
		default:
		{
			result = getInstance().dispatchMessage (hWnd, message, wParam, lParam);
			break;
		}
    }
	
	return result;
}

void MessageDispatcher::unregisterControllerByHandle(HWND hWnd) {
	auto controller = mMessageHandlers[hWnd];
	
	mMessageHandlers.erase (hWnd);
	
	std::shared_ptr<INotificationHandler> notificationHandler = std::dynamic_pointer_cast<INotificationHandler>(controller);
	if (notificationHandler) {
		mNotificationHandlers.erase (notificationHandler->getCommandId());
	}
}

void MessageDispatcher::unregisterControllerById(int id) {
	auto controller = mNotificationHandlers[id];
	
	mNotificationHandlers.erase (id);
	
	std::shared_ptr<IMessageHandler> messageHandler = std::dynamic_pointer_cast<IMessageHandler>(controller);
	if (messageHandler) {
		mMessageHandlers.erase (messageHandler->getHWnd());
	}
}

LRESULT MessageDispatcher::dispatchMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	try {
		auto controllerItor = mMessageHandlers.find (hWnd);
		// If does not exist a registered controller call DefWindowProc
		if (controllerItor == mMessageHandlers.end()) {
			return ::DefWindowProc (hWnd, message, wParam, lParam);
		}
		
		// Let the controller handle this message
		auto controller = controllerItor->second;
		LRESULT result = 0;
		if (!controller->handleMessage (message, wParam, lParam, result)) {
			return controller->callDefWindowProc (hWnd, message, wParam, lParam);
		}
		
		return result;
	} catch (std::exception& e) {
		std::string error_message = "An unhandled exception occurred.\n";
		error_message += e.what();
		
		int res = ::MessageBox(NULL,
		                     error_message.c_str(),
		                     "Unhandled exception",
		                     MB_ICONERROR | MB_RETRYCANCEL);

		if (res & IDRETRY) {
			return ::DefWindowProc (hWnd, message, wParam, lParam);
		} else {
			exit (EXIT_FAILURE);
		}
	}
}

LRESULT MessageDispatcher::dispatchCommand(WPARAM wParam, LPARAM lParam) {
	try {
		int commandId = LOWORD(wParam);
		
		auto controllerItor = mNotificationHandlers.find (commandId);
		if (controllerItor == mNotificationHandlers.end()) {
			return 0;
		}

		auto controller = controllerItor->second;
		controller->handleCommand (wParam, lParam);

		return 0;
	} catch (std::exception& e) {
		
		std::string error_message = "An unhandled exception occurred.\n";
		error_message += e.what();
		
		int res = ::MessageBox(NULL,
		                     error_message.c_str(),
		                     "Unhandled exception",
		                     MB_ICONERROR | MB_RETRYCANCEL);

		if (res & IDRETRY) {
			return 0;
		} else {
			exit (EXIT_FAILURE);
		}
	}	
}

}


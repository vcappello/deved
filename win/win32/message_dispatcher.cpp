#include "message_dispatcher.h"

namespace win {
	
MessageDispatcher::MessageDispatcher()
{
}

MessageDispatcher::~MessageDispatcher()
{
}

MessageDispatcher& MessageDispatcher::getInstance() {
	static MessageDispatcher instance;
	
	return instance;
}

void MessageDispatcher::unregisterControllerByHandle(HWND hWnd)
{
	auto controller = controllerMap[hWnd];
	
	controllerMap.erase (hWnd);
	
	std::shared_ptr<ICommandable> commandable = std::dynamic_pointer_cast<ICommandable>(controller);
	if (commandable) {
		controllerCmdMap.erase (commandable->getCommandId());
	}
}

LRESULT MessageDispatcher::dispatchMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	try {
		auto controllerItor = controllerMap.find (hWnd);
		if (controllerItor == controllerMap.end()) {
			return ::DefWindowProc (hWnd, message, wParam, lParam);
		}
		
		std::shared_ptr<IMessageable> controller = controllerItor->second;
		LRESULT result = 0;
		if (!controller->handleMessage (message, wParam, lParam, result)) {
			return ::DefWindowProc (hWnd, message, wParam, lParam);
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

LRESULT MessageDispatcher::dispatchCommand(WPARAM wParam, LPARAM lParam)
{
	try {
		int commandId = LOWORD(wParam);
		
		auto controllerItor = controllerCmdMap.find (commandId);
		if (controllerItor == controllerCmdMap.end()) {
			return 0;
		}

		std::shared_ptr<ICommandable> controller = controllerItor->second;
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


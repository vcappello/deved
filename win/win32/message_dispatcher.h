/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_MESSAGE_DISPATCHER_H
#define WIN_WIN32_MESSAGE_DISPATCHER_H

#include <win/window.h>
#include "i_messageable.h"
#include "i_commandable.h"

#include <memory>
#include <map>
#include <windows.h>

namespace win {

class MessageDispatcher {
private:
	MessageDispatcher();
	MessageDispatcher(const MessageDispatcher&);
	void operator=(const MessageDispatcher&);

public:
	virtual ~MessageDispatcher();
	
	static MessageDispatcher& getInstance();

	template<class T>
	void registerController(std::shared_ptr<T> controller) {
		std::shared_ptr<IMessageable> messageable = std::dynamic_pointer_cast<IMessageable>(controller);
		if (messageable) {
			controllerMap.insert (std::make_pair (messageable->getHWnd(), messageable));
		}
		
		std::shared_ptr<ICommandable> commandable = std::dynamic_pointer_cast<ICommandable>(controller);
		if (commandable) {
			controllerCmdMap.insert (std::make_pair (commandable->getCommandId(), commandable));
		}		
	}
	
	void unregisterControllerByHandle(HWND hWnd);
	// TODO: need to implement void unregisterControllerById(int id);
	
	LRESULT dispatchMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	LRESULT dispatchCommand(WPARAM wParam, LPARAM lParam);

private:
	std::map<HWND, std::shared_ptr<IMessageable>> controllerMap;
	std::map<int, std::shared_ptr<ICommandable>> controllerCmdMap;
};

}

#endif // WIN_WIN32_MESSAGE_DISPATCHER_H

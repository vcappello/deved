/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_MESSAGE_LOOP_H
#define WIN_WIN32_MESSAGE_LOOP_H

#include <windows.h>

namespace win {

class MessageLoop {
private:
	MessageLoop();
	MessageLoop(const MessageLoop&);
	void operator=(const MessageLoop&);

public:
	virtual ~MessageLoop();
	
	static MessageLoop& getInstance();

	void setActiveWindowHWnd (HWND hWnd);

	int start();

private:
	HWND mActiveWindowHWnd;
};

}

#endif // WIN_WIN32_MESSAGE_LOOP_H

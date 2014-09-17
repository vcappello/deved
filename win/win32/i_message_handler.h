/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_I_MESSAGEABLE_H
#define WIN_WIN32_I_MESSAGEABLE_H

#include <windows.h>

namespace win {

/**
 * Interface for controllers that can manage messages
 */
class IMessageHandler
{
public:
	IMessageHandler() {
	}
	virtual ~IMessageHandler() {
	}

public:
	virtual HWND getHWnd() = 0;
	
	virtual bool handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult) = 0;

	virtual LRESULT callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};

}

#endif // WIN_WIN32_I_MESSAGEABLE_H

/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_I_MESSAGEABLE_H
#define WIN_WIN32_I_MESSAGEABLE_H

#include <windows.h>

namespace win {

class IMessageable
{
public:
	IMessageable() {
	}
	virtual ~IMessageable() {
	}

public:
	virtual HWND getHWnd() = 0;
	
	virtual bool handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult) = 0;
};

}

#endif // WIN_WIN32_I_MESSAGEABLE_H

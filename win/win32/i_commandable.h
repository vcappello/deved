/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_I_COMMANDABLE_H
#define WIN_WIN32_I_COMMANDABLE_H

#include <windows.h>

namespace win {

class ICommandable
{
public:
	ICommandable() {
	}
	virtual ~ICommandable() {
	}

public:
	virtual int getCommandId() const = 0;
	
	virtual void handleCommand(WPARAM wParam, LPARAM lParam) = 0;
};

}

#endif // WIN_WIN32_I_COMMANDABLE_H

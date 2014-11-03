/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_SUBCLASS_HANDLER_H
#define WIN_WIN32_SUBCLASS_HANDLER_H

#include <memory>
#include <windows.h>

namespace win {

class SubclassHandler {
public:
	explicit SubclassHandler(HWND hWnd);
	virtual ~SubclassHandler();

	LRESULT callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	static std::unique_ptr<SubclassHandler> create(HWND hWnd);

protected:
	HWND mHWnd;
	WNDPROC mOldWndProc;
};

}

#endif // WIN_WIN32_SUBCLASS_HANDLER_H


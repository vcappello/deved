/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_WINDOW_CONTAINER_BASE_H
#define WIN_WIN32_WINDOW_CONTAINER_BASE_H

#include "window_base.h"
#include <windows.h>

namespace win {

class WindowContainerBase : public WindowBase {
public:
	explicit WindowContainerBase(HWND hWnd);
	virtual ~WindowContainerBase();

	void addChildWindow(const std::string& name, std::shared_ptr<WindowBase> child);

protected:
};

}

#endif // WIN_WIN32_WINDOW_CONTAINER_BASE_H

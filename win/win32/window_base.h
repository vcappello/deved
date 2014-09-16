/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_WINDOW_BASE_H
#define WIN_WIN32_WINDOW_BASE_H

#include "i_messageable.h"
#include <win/point.h>
#include <win/size.h>

#include <string>
#include <vector>
#include <windows.h>

namespace win {

class WindowBase : public IMessageable {
public:
	explicit WindowBase(HWND hWnd);
	virtual ~WindowBase();

	Point getPosition();
	void setPosition(const Point& value);

	Size getSize();
	void setSize(const Size& size);

	std::string getText();
	void setText(std::string& value);
	
protected:
	HWND mHWnd;
};

}

#endif // WIN_WIN32_WINDOW_BASE_H

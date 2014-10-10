/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_WINDOW_BASE_H
#define WIN_WIN32_WINDOW_BASE_H

#include "i_message_handler.h"
#include "windows_object.h"
#include "message_dispatcher.h"
#include "font_resource.h"
#include <win/point.h>
#include <win/size.h>

#include <string>
#include <vector>
#include <windows.h>

namespace win {

class WindowBase : public IMessageHandler,
                   public WindowsObject {
public:
	explicit WindowBase(HWND hWnd);
	virtual ~WindowBase();

	Point getPosition();
	void setPosition(const Point& value);

	Size getSize();
	void setSize(const Size& size);

	std::string getText();
	void setText(std::string& value);
	
	bool isVisible();
	void setVisible(bool value);

	bool isEnabled();
	void setEnabled(bool value);

	bool hasBorder();
	void setBorder(bool value);

	std::shared_ptr<FontResource> getFontResource();
	void setFontResource(std::shared_ptr<FontResource> fontResource);

	int getDefaultId();
	void setDefaultId(int id);
	
	bool getStyleBit(DWORD flag);
	void setStyleBit(DWORD flag, bool value);

	bool getExStyleBit(DWORD flag);
	void setExStyleBit(DWORD flag, bool value);
	
	HWND getTopLevelHWnd();
	
	/** @name IMessageHandler implementations
	 */
	///@{ 
	HWND getHWnd() { return mHWnd; }
	
	// bool handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult); // Abstract

	// LRESULT callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // Abstract
	///@}
	
	/** @name WindowsObject overrides
	 */
	///@{ 
	void destroy();
	///@}
	
protected:
	HWND mHWnd;
	std::string mCurrentFontResourceName;
};

}

#endif // WIN_WIN32_WINDOW_BASE_H

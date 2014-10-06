/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_FONT_RESOURCE_H
#define WIN_WIN32_FONT_RESOURCE_H

#include "windows_object.h"
#include <win/font.h>
#include <win/event.h>

#include <windows.h>

namespace win {
	
class FontResource : public WindowsObject {
public:
	FontResource(HFONT hFont, std::shared_ptr<Font> font);
	virtual ~FontResource();

	HFONT getHFont() { return mHFont; }
	
	std::shared_ptr<Font> getFont() { return mFont; }
	
	Event<> changedEvent;
	
protected:
	HFONT mHFont;
	std::shared_ptr<Font> mFont;

protected:
	void regenerateHFont();
};

}

#endif // WIN_WIN32_FONT_RESOURCE_H


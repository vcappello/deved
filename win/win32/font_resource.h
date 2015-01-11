/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_FONT_RESOURCE_H
#define WIN_WIN32_FONT_RESOURCE_H

#include "resource_item.h"
#include <win/font.h>
#include <win/event.h>

#include <windows.h>

namespace win {

/**
 * Manage font model and font handler.
 * When the font model was modified the class generate a new font handler.
 */	
class FontResource : public ResourceItem {
public:
	FontResource(HFONT hFont, std::shared_ptr<Font> font);
	virtual ~FontResource();

	HFONT getHFont() { return mHFont; }
	void setHFont(HFONT hFont);
	
	std::shared_ptr<Font> getFont() { return mFont; }
	
	/**
	 * Event raised when a property of the model is changed. In this case
	 * a new font handler is generated. The parent must select the new font handler.
	 */
	Event<> changedEvent;
	
protected:
	HFONT mHFont;
	std::shared_ptr<Font> mFont;

protected:
	void regenerateHFont();
	void updateModelFromLogFont(const LOGFONT& logFont);	
};

}

#endif // WIN_WIN32_FONT_RESOURCE_H


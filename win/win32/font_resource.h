/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_FONT_RESOURCE_H
#define WIN_WIN32_FONT_RESOURCE_H

#include "windows_object.h"

#include <windows.h>

namespace win {
	
class FontResource : public WindowsObject {
public:
	FontResource(HFONT hFont);
	virtual ~FontResource();

protected:
	HFONT mHFont;
};

}

#endif // WIN_WIN32_FONT_RESOURCE_H


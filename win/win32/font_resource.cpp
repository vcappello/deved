#include "font_resource.h"

namespace win {

FontResource::FontResource(HFONT hFont, std::shared_ptr<Font> font) :
	mHFont( hFont ),
	mFont( font ) {
		
	mFont->fontName.changedEvent.add([&]{ changedEvent.fire(); });
	mFont->size.changedEvent.add([&]{ changedEvent.fire(); });
	mFont->bold.changedEvent.add([&]{ changedEvent.fire(); });
	mFont->italic.changedEvent.add([&]{ changedEvent.fire(); });
	mFont->underline.changedEvent.add([&]{ changedEvent.fire(); });
}

FontResource::~FontResource() {
	::DeleteObject (mHFont);
}


}


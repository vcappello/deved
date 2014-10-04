#include "font_resource.h"

namespace win {

FontResource::FontResource(HFONT hFont, std::shared_ptr<Font> font) :
	mHFont( hFont ),
	mFont( font ) {
}

FontResource::~FontResource() {
	::DeleteObject (mHFont);
}


}


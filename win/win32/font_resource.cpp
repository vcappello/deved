#include "font_resource.h"

namespace win {

FontResource::FontResource(HFONT hFont) :
	mHFont( hFont ) {
}

FontResource::~FontResource() {
	::DeleteObject (mHFont);
}

}


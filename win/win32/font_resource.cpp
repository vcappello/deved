#include "font_resource.h"

#include "control_factory.h"

namespace win {

FontResource::FontResource(HFONT hFont, std::shared_ptr<Font> font) :
	mHFont( hFont ),
	mFont( font ) {
		
	mFont->fontName.changedEvent.add ([&]{ regenerateHFont(); });
	mFont->size.changedEvent.add ([&]{ regenerateHFont(); });
	mFont->bold.changedEvent.add ([&]{ regenerateHFont(); });
	mFont->italic.changedEvent.add ([&]{ regenerateHFont(); });
	mFont->underline.changedEvent.add ([&]{ regenerateHFont(); });
}

FontResource::~FontResource() {
	::DeleteObject (mHFont);
}

void FontResource::updateModelFromLogFont(const LOGFONT& logFont) {
	auto newFont = createFont (logFont);
	mFont->fontName (newFont->fontName());
	mFont->size (newFont->size());
	mFont->bold (newFont->bold());
	mFont->italic (newFont->italic());
	mFont->underline (newFont->underline());
}

void FontResource::regenerateHFont() {
	HFONT oldHFont = mHFont;
	
	// Create the new font handler
	mHFont = createHFont (mFont);
	
	// Notify parent, here the owner must select the new font
	changedEvent.fire();
	
	// Delete previous object
	::DeleteObject (oldHFont);
}

}


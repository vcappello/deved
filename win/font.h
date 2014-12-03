/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_FONT_H
#define WIN_FONT_H

#include <win/i_entity.h>
#include <win/property.h>

#include <memory>
#include <string>
#include <utility>

namespace win {

class Font : public IEntity {
public:
	Font(const std::string& fontName, int size, bool bold, bool italic, bool underline) :
		fontName( fontName ),
		size( size ),
		bold( bold ), 
		italic( italic ),
		underline( underline ) {
	}
	Font(const std::string& fontName, int size) :
		Font( fontName, size, false, false, false ) {
	}	
	explicit Font(const std::string& fontName) :
		Font( fontName, 0 ) {
	}
	virtual ~Font() {
	}
	
	/** @name IEntity implementations
	 */
	///@{ 	
	virtual std::string getType() const { return "Font"; }
	///@}
	
public:
	Property<std::string> fontName;
	Property<int> size;
	Property<bool> bold;
	Property<bool> italic;
	Property<bool> underline;
};

}

#endif // WIN_FONT_H

/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_FONT_H
#define WIN_FONT_H

#include <win/entity.h>
#include <win/property.h>

#include <memory>
#include <string>
#include <utility>

namespace win {

class Font : public Entity {
public:
	explicit Font(const std::string& name) :
		name( name ),
		fontName( "" ),
		size( 0 ),
		bold( false ), 
		italic( false ),
		underline( false ) {
	}
	Font(const std::string& name, const std::string& fontName, int size) :
		name( name ),
		fontName( fontName ),
		size( size ),
		bold( false ), 
		italic( false ),
		underline( false ) {
	}
	Font(const std::string& name, const std::string& fontName, int size, bool bold, bool italic, bool underline) :
		name( name ),
		fontName( fontName ),
		size( size ),
		bold( bold ), 
		italic( italic ),
		underline( underline ) {
	}		
	virtual ~Font() {
	}
	
	/** @name Entity implementations
	 */
	///@{ 	
	virtual std::string getType() const { return "Font"; }
	
	virtual std::string getName() const { return name(); }
	///@}
	
public:
	Property<std::string> name;
	Property<std::string> fontName;
	Property<int> size;
	Property<bool> bold;
	Property<bool> italic;
	Property<bool> underline;
};

}

#endif // WIN_FONT_H

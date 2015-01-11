/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_COLOR_H
#define WIN_COLOR_H

#include <win/i_entity.h>
#include <win/property.h>

namespace win {

class Color : public IEntity {
public:
	explicit Color(uint32_t value) :
		value( value ) {
	}	
	virtual ~Color() {
	}
	
	/** @name IEntity implementations
	 */
	///@{ 
	virtual std::string getType() const { return "Color"; }
	///@}
	
	static std::shared_ptr<Color> rgb(uint8_t r, uint8_t g, uint8_t b) {
		uint32_t value = (static_cast<uint32_t>(b) << 16) | 
			(static_cast<uint32_t>(g) << 8) | 
			(static_cast<uint32_t>(r));
		
		return std::make_shared<Color>( value );
	}
	
public:
	/** @name Properties
	 */
	///@{ 
	Property<uint32_t> value;
	///@}
};

}
 
#endif //  WIN_COLOR_H
 
 
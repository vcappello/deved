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
	
public:	
	static std::shared_ptr<Color> rgb(uint8_t r, uint8_t g, uint8_t b) {
		uint32_t value = (static_cast<uint32_t>(b) << 16) | 
			(static_cast<uint32_t>(g) << 8) | 
			(static_cast<uint32_t>(r));
		
		return std::make_shared<Color>( value );
	}
	
	static std::shared_ptr<Color> hex(uint32_t hex) {
		uint32_t value = ((hex & 0x00ff0000) >> 16) | 
			(hex & 0x0000ff00) | 
			((hex & 0x000000ff) << 16);
		
		return std::make_shared<Color>( value );
	}	
	
public:
	static std::shared_ptr<Color> makeAliceBlue() { return Color::hex (0xF0F8FF); }
	static std::shared_ptr<Color> makeAntiqueWhite() { return Color::hex (0xFAEBD7); }
	static std::shared_ptr<Color> makeAqua() { return Color::hex (0x00FFFF); }
	static std::shared_ptr<Color> makeAquamarine() { return Color::hex (0x7FFFD4); }
	static std::shared_ptr<Color> makeAzure() { return Color::hex (0xF0FFFF); }
	static std::shared_ptr<Color> makeBeige() { return Color::hex (0xF5F5DC); }
	static std::shared_ptr<Color> makeBisque() { return Color::hex (0xFFE4C4); }
	static std::shared_ptr<Color> makeBlack() { return Color::hex (0x000000); }
	static std::shared_ptr<Color> makeBlanchedAlmond() { return Color::hex (0xFFEBCD); }
	static std::shared_ptr<Color> makeBlue() { return Color::hex (0x0000FF); }
	static std::shared_ptr<Color> makeBlueViolet() { return Color::hex (0x8A2BE2); }
	static std::shared_ptr<Color> makeBrown() { return Color::hex (0xA52A2A); }
	static std::shared_ptr<Color> makeBurlyWood() { return Color::hex (0xDEB887); }
	static std::shared_ptr<Color> makeCadetBlue() { return Color::hex (0x5F9EA0); }
	static std::shared_ptr<Color> makeChartreuse() { return Color::hex (0x7FFF00); }
	static std::shared_ptr<Color> makeChocolate() { return Color::hex (0xD2691E); }
	static std::shared_ptr<Color> makeCoral() { return Color::hex (0xFF7F50); }
	static std::shared_ptr<Color> makeCornflowerBlue() { return Color::hex (0x6495ED); }
	static std::shared_ptr<Color> makeCornsilk() { return Color::hex (0xFFF8DC); }
	static std::shared_ptr<Color> makeCrimson() { return Color::hex (0xDC143C); }
	static std::shared_ptr<Color> makeCyan() { return Color::hex (0x00FFFF); }
	static std::shared_ptr<Color> makeDarkBlue() { return Color::hex (0x00008B); }
	static std::shared_ptr<Color> makeDarkCyan() { return Color::hex (0x008B8B); }
	static std::shared_ptr<Color> makeDarkGoldenRod() { return Color::hex (0xB8860B); }
	static std::shared_ptr<Color> makeDarkGray() { return Color::hex (0xA9A9A9); }
	static std::shared_ptr<Color> makeDarkGreen() { return Color::hex (0x006400); }
	static std::shared_ptr<Color> makeDarkKhaki() { return Color::hex (0xBDB76B); }
	static std::shared_ptr<Color> makeDarkMagenta() { return Color::hex (0x8B008B); }
	static std::shared_ptr<Color> makeDarkOliveGreen() { return Color::hex (0x556B2F); }
	static std::shared_ptr<Color> makeDarkOrange() { return Color::hex (0xFF8C00); }
	static std::shared_ptr<Color> makeDarkOrchid() { return Color::hex (0x9932CC); }
	static std::shared_ptr<Color> makeDarkRed() { return Color::hex (0x8B0000); }
	static std::shared_ptr<Color> makeDarkSalmon() { return Color::hex (0xE9967A); }
	static std::shared_ptr<Color> makeDarkSeaGreen() { return Color::hex (0x8FBC8F); }
	static std::shared_ptr<Color> makeDarkSlateBlue() { return Color::hex (0x483D8B); }
	static std::shared_ptr<Color> makeDarkSlateGray() { return Color::hex (0x2F4F4F); }
	static std::shared_ptr<Color> makeDarkTurquoise() { return Color::hex (0x00CED1); }
	static std::shared_ptr<Color> makeDarkViolet() { return Color::hex (0x9400D3); }
	static std::shared_ptr<Color> makeDeepPink() { return Color::hex (0xFF1493); }
	static std::shared_ptr<Color> makeDeepSkyBlue() { return Color::hex (0x00BFFF); }
	static std::shared_ptr<Color> makeDimGray() { return Color::hex (0x696969); }
	static std::shared_ptr<Color> makeDodgerBlue() { return Color::hex (0x1E90FF); }
	static std::shared_ptr<Color> makeFireBrick() { return Color::hex (0xB22222); }
	static std::shared_ptr<Color> makeFloralWhite() { return Color::hex (0xFFFAF0); }
	static std::shared_ptr<Color> makeForestGreen() { return Color::hex (0x228B22); }
	static std::shared_ptr<Color> makeFuchsia() { return Color::hex (0xFF00FF); }
	static std::shared_ptr<Color> makeGainsboro() { return Color::hex (0xDCDCDC); }
	static std::shared_ptr<Color> makeGhostWhite() { return Color::hex (0xF8F8FF); }
	static std::shared_ptr<Color> makeGold() { return Color::hex (0xFFD700); }
	static std::shared_ptr<Color> makeGoldenRod() { return Color::hex (0xDAA520); }
	static std::shared_ptr<Color> makeGray() { return Color::hex (0x808080); }
	static std::shared_ptr<Color> makeGreen() { return Color::hex (0x008000); }
	static std::shared_ptr<Color> makeGreenYellow() { return Color::hex (0xADFF2F); }
	static std::shared_ptr<Color> makeHoneyDew() { return Color::hex (0xF0FFF0); }
	static std::shared_ptr<Color> makeHotPink() { return Color::hex (0xFF69B4); }
	static std::shared_ptr<Color> makeIndianRed() { return Color::hex (0xCD5C5C); }
	static std::shared_ptr<Color> makeIndigo() { return Color::hex (0x4B0082); }
	static std::shared_ptr<Color> makeIvory() { return Color::hex (0xFFFFF0); }
	static std::shared_ptr<Color> makeKhaki() { return Color::hex (0xF0E68C); }
	static std::shared_ptr<Color> makeLavender() { return Color::hex (0xE6E6FA); }
	static std::shared_ptr<Color> makeLavenderBlush() { return Color::hex (0xFFF0F5); }
	static std::shared_ptr<Color> makeLawnGreen() { return Color::hex (0x7CFC00); }
	static std::shared_ptr<Color> makeLemonChiffon() { return Color::hex (0xFFFACD); }
	static std::shared_ptr<Color> makeLightBlue() { return Color::hex (0xADD8E6); }
	static std::shared_ptr<Color> makeLightCoral() { return Color::hex (0xF08080); }
	static std::shared_ptr<Color> makeLightCyan() { return Color::hex (0xE0FFFF); }
	static std::shared_ptr<Color> makeLightGoldenRodYellow() { return Color::hex (0xFAFAD2); }
	static std::shared_ptr<Color> makeLightGray() { return Color::hex (0xD3D3D3); }
	static std::shared_ptr<Color> makeLightGreen() { return Color::hex (0x90EE90); }
	static std::shared_ptr<Color> makeLightPink() { return Color::hex (0xFFB6C1); }
	static std::shared_ptr<Color> makeLightSalmon() { return Color::hex (0xFFA07A); }
	static std::shared_ptr<Color> makeLightSeaGreen() { return Color::hex (0x20B2AA); }
	static std::shared_ptr<Color> makeLightSkyBlue() { return Color::hex (0x87CEFA); }
	static std::shared_ptr<Color> makeLightSlateGray() { return Color::hex (0x778899); }
	static std::shared_ptr<Color> makeLightSteelBlue() { return Color::hex (0xB0C4DE); }
	static std::shared_ptr<Color> makeLightYellow() { return Color::hex (0xFFFFE0); }
	static std::shared_ptr<Color> makeLime() { return Color::hex (0x00FF00); }
	static std::shared_ptr<Color> makeLimeGreen() { return Color::hex (0x32CD32); }
	static std::shared_ptr<Color> makeLinen() { return Color::hex (0xFAF0E6); }
	static std::shared_ptr<Color> makeMagenta() { return Color::hex (0xFF00FF); }
	static std::shared_ptr<Color> makeMaroon() { return Color::hex (0x800000); }
	static std::shared_ptr<Color> makeMediumAquaMarine() { return Color::hex (0x66CDAA); }
	static std::shared_ptr<Color> makeMediumBlue() { return Color::hex (0x0000CD); }
	static std::shared_ptr<Color> makeMediumOrchid() { return Color::hex (0xBA55D3); }
	static std::shared_ptr<Color> makeMediumPurple() { return Color::hex (0x9370DB); }
	static std::shared_ptr<Color> makeMediumSeaGreen() { return Color::hex (0x3CB371); }
	static std::shared_ptr<Color> makeMediumSlateBlue() { return Color::hex (0x7B68EE); }
	static std::shared_ptr<Color> makeMediumSpringGreen() { return Color::hex (0x00FA9A); }
	static std::shared_ptr<Color> makeMediumTurquoise() { return Color::hex (0x48D1CC); }
	static std::shared_ptr<Color> makeMediumVioletRed() { return Color::hex (0xC71585); }
	static std::shared_ptr<Color> makeMidnightBlue() { return Color::hex (0x191970); }
	static std::shared_ptr<Color> makeMintCream() { return Color::hex (0xF5FFFA); }
	static std::shared_ptr<Color> makeMistyRose() { return Color::hex (0xFFE4E1); }
	static std::shared_ptr<Color> makeMoccasin() { return Color::hex (0xFFE4B5); }
	static std::shared_ptr<Color> makeNavajoWhite() { return Color::hex (0xFFDEAD); }
	static std::shared_ptr<Color> makeNavy() { return Color::hex (0x000080); }
	static std::shared_ptr<Color> makeOldLace() { return Color::hex (0xFDF5E6); }
	static std::shared_ptr<Color> makeOlive() { return Color::hex (0x808000); }
	static std::shared_ptr<Color> makeOliveDrab() { return Color::hex (0x6B8E23); }
	static std::shared_ptr<Color> makeOrange() { return Color::hex (0xFFA500); }
	static std::shared_ptr<Color> makeOrangeRed() { return Color::hex (0xFF4500); }
	static std::shared_ptr<Color> makeOrchid() { return Color::hex (0xDA70D6); }
	static std::shared_ptr<Color> makePaleGoldenRod() { return Color::hex (0xEEE8AA); }
	static std::shared_ptr<Color> makePaleGreen() { return Color::hex (0x98FB98); }
	static std::shared_ptr<Color> makePaleTurquoise() { return Color::hex (0xAFEEEE); }
	static std::shared_ptr<Color> makePaleVioletRed() { return Color::hex (0xDB7093); }
	static std::shared_ptr<Color> makePapayaWhip() { return Color::hex (0xFFEFD5); }
	static std::shared_ptr<Color> makePeachPuff() { return Color::hex (0xFFDAB9); }
	static std::shared_ptr<Color> makePeru() { return Color::hex (0xCD853F); }
	static std::shared_ptr<Color> makePink() { return Color::hex (0xFFC0CB); }
	static std::shared_ptr<Color> makePlum() { return Color::hex (0xDDA0DD); }
	static std::shared_ptr<Color> makePowderBlue() { return Color::hex (0xB0E0E6); }
	static std::shared_ptr<Color> makePurple() { return Color::hex (0x800080); }
	static std::shared_ptr<Color> makeRed() { return Color::hex (0xFF0000); }
	static std::shared_ptr<Color> makeRosyBrown() { return Color::hex (0xBC8F8F); }
	static std::shared_ptr<Color> makeRoyalBlue() { return Color::hex (0x4169E1); }
	static std::shared_ptr<Color> makeSaddleBrown() { return Color::hex (0x8B4513); }
	static std::shared_ptr<Color> makeSalmon() { return Color::hex (0xFA8072); }
	static std::shared_ptr<Color> makeSandyBrown() { return Color::hex (0xF4A460); }
	static std::shared_ptr<Color> makeSeaGreen() { return Color::hex (0x2E8B57); }
	static std::shared_ptr<Color> makeSeaShell() { return Color::hex (0xFFF5EE); }
	static std::shared_ptr<Color> makeSienna() { return Color::hex (0xA0522D); }
	static std::shared_ptr<Color> makeSilver() { return Color::hex (0xC0C0C0); }
	static std::shared_ptr<Color> makeSkyBlue() { return Color::hex (0x87CEEB); }
	static std::shared_ptr<Color> makeSlateBlue() { return Color::hex (0x6A5ACD); }
	static std::shared_ptr<Color> makeSlateGray() { return Color::hex (0x708090); }
	static std::shared_ptr<Color> makeSnow() { return Color::hex (0xFFFAFA); }
	static std::shared_ptr<Color> makeSpringGreen() { return Color::hex (0x00FF7F); }
	static std::shared_ptr<Color> makeSteelBlue() { return Color::hex (0x4682B4); }
	static std::shared_ptr<Color> makeTan() { return Color::hex (0xD2B48C); }
	static std::shared_ptr<Color> makeTeal() { return Color::hex (0x008080); }
	static std::shared_ptr<Color> makeThistle() { return Color::hex (0xD8BFD8); }
	static std::shared_ptr<Color> makeTomato() { return Color::hex (0xFF6347); }
	static std::shared_ptr<Color> makeTurquoise() { return Color::hex (0x40E0D0); }
	static std::shared_ptr<Color> makeViolet() { return Color::hex (0xEE82EE); }
	static std::shared_ptr<Color> makeWheat() { return Color::hex (0xF5DEB3); }
	static std::shared_ptr<Color> makeWhite() { return Color::hex (0xFFFFFF); }
	static std::shared_ptr<Color> makeWhiteSmoke() { return Color::hex (0xF5F5F5); }
	static std::shared_ptr<Color> makeYellow() { return Color::hex (0xFFFF00); }
	static std::shared_ptr<Color> makeYellowGreen() { return Color::hex (0x9ACD32); }
	
public:
	/** @name Properties
	 */
	///@{ 
	Property<uint32_t> value;
	///@}
};

}
 
#endif //  WIN_COLOR_H
 
 
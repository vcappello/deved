/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_SIZE_H
#define WIN_SIZE_H

namespace win {

class Size {
public:
	Size() {}
	Size(int width, int height) :
		width( width ),
		height( height ) {}
	~Size() {}

	int width;
	int height;
};

}

#endif // WIN_SIZE_H
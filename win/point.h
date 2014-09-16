/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_POINT_H
#define WIN_POINT_H

namespace win {

class Point {
public:
	Point() {}
	Point(int x, int y) :
		x( x ),
		y( y ) {}		
	~Point() {}

	int x;
	int y;
};

}

#endif // WIN_POINT_H
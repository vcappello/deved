/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_CREATE_WINDOW_H
#define WIN_CREATE_WINDOW_H

#include <win/window.h>
#include <win/error.h>
#include <win/font.h>

#include <memory>

namespace win {
	
void createWindow(std::shared_ptr<Window> window);
	
int run();

std::shared_ptr<Font> getSystemFont();
		
}

#endif // WIN_CREATE_WINDOW_H



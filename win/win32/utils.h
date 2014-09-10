/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_UTILS_H
#define WIN_WIN32_UTILS_H

#include <string>
#include <windows.h>

namespace win {
	
std::string formatSystemMessage(DWORD code);
	
}

#endif // WIN_WIN32_UTILS_H

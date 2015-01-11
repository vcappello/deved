/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_GDI_OBJECT_H
#define WIN_WIN32_GDI_OBJECT_H

#include "resource_item.h"

#include <windows.h>

namespace win {

template<class T>
class GdiObject : public ResourceItem {
public:
	GdiObject(const T& handle) :
		mHandle( handle ) {
	}
	virtual ~GdiObject() {
		::DeleteObject (mHandle);
	}
	
	T getHandle() const { return mHandle; }
	
protected:
	T mHandle;
};

}

#endif // WIN_WIN32_FONT_RESOURCE_H




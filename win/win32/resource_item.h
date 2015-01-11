/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_RESOURCE_ITEM_H
#define WIN_WIN32_RESOURCE_ITEM_H

namespace win {
	
class ResourceItem {
public:
	ResourceItem();
	virtual ~ResourceItem();

	virtual void destroy();
};

}

#endif // WIN_WIN32_RESOURCE_ITEM_H


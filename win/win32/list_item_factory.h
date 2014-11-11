/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_LIST_ITEM_FACTORY_H
#define WIN_WIN32_LIST_ITEM_FACTORY_H

#include "list_item_controller.h"
#include "text_list_item_controller.h"
#include "list_box_controller.h"

#include <memory>

namespace win {

std::shared_ptr<ListItemController> createListItemController(std::shared_ptr<ListBoxController> container, std::shared_ptr<ListItem> listItem);

std::shared_ptr<TextListItemController> createTextListItemController(std::shared_ptr<ListBoxController> container, std::shared_ptr<TextListItem> textListItem);
	
}

#endif // WIN_WIN32_LIST_ITEM_FACTORY_H


#include "list_item_factory.h"

namespace win {

std::shared_ptr<ListItemController> createListItemController(std::shared_ptr<ListBoxController> container, std::shared_ptr<ListItem> listItem) {
	std::shared_ptr<ListItemController> controller;
	if (listItem->getType() == "TextListItem") {
		auto textListItem = std::dynamic_pointer_cast<TextListItem>( listItem );
		if (!textListItem) {
			throw Error( "Can not create list-item '" + listItem->name() + "'" );
		}
		controller = createTextListItemController (container, textListItem);
	} else {
		throw Error( "Can not create list-item '" + listItem->name() + "' unknown type '" + listItem->getType() + "'" );
	}
	
	return controller;
}

std::shared_ptr<TextListItemController> createTextListItemController(std::shared_ptr<ListBoxController> container, std::shared_ptr<TextListItem> textListItem) {
	int index = ::SendMessage (container->getHWnd(), LB_ADDSTRING, 0, reinterpret_cast<WPARAM>( textListItem->text().c_str() ));
	if (index == LB_ERR) {
		throw Error( "Can not create list-item (LB_ADDSTRING)" );
	}
	
	::SendMessage (container->getHWnd(), LB_SETITEMDATA, index, reinterpret_cast<LPARAM>(textListItem.get()));
	
	std::shared_ptr<TextListItemController> controller = std::make_shared<TextListItemController>( index, container->getHWnd(), textListItem );
	return controller;
}
	
}


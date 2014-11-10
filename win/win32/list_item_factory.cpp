#include "list_item_factory.h"

namespace win {

std::unique_ptr<ListItemController> createListItem(std::shared_ptr<ListBoxController> container, std::shared_ptr<ListItem> listItem) {
	std::unique_ptr<ListItemController> listItemController;
	if (listItem->getType() == "TextListItem") {
		auto textListItem = std::dynamic_pointer_cast<TextListItem>( listItem );
		if (!textListItem) {
			throw Error( "Can not create list-item '" + listItem->getName() + "'" );
		}
		listItemController = createTextListItem (container, textListItem);
	} else {
		throw Error( "Can not create list-item '" + listItem->getName() + "' unknown type '" + listItem->getType() + "'" );
	}
	
	return listItem;
}

std::unique_ptr<TextListItemController> createTextListItem(std::shared_ptr<ListBoxController> container, std::shared_ptr<TextListItem> textListItem) {
	int index = ::SendMessage (container->getHWnd(), LB_ADDSTRING, 0, textListItem->text());
	if (index == LB_ERR) {
		throw Error( "Can not create list-item (LB_ADDSTRING)" );
	}
	
	std::unique_ptr<TextListItemController> controller( new TextListItemController( index, containe->getHWnd(), textListItem ) );
	return controller;
}
	
}


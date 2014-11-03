/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_TEXT_LIST_ITEM_H
#define WIN_TEXT_LIST_ITEM_H

#include <win/list_item.h>

namespace win {
	
/**
 * Text-only ListBoxItem
 */
class TextListItem : public ListItem {
public:
	explicit TextListItem(const std::string& name) :
		ListItem( name ) {
	}
	TextListItem(const std::string& name, const std::string& text) :
		ListItem( name ),
		text( text ) {
	}
	virtual ~TextListItem() {
	}
	
	/** @name IEntity implementations
	 */
	///@{ 	
	virtual std::string getType() const { return "TextListItem"; }
	///@}
	
public:
	/** @name Properties
	 */
	///@{ 	
	Property<std::string> text;
	///@}

	/** @name Events
	 */
	///@{ 
	///@}
};

}

#endif // WIN_TEXT_LIST_ITEM_H


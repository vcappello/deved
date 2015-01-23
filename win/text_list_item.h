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
	TextListItem(const std::string& name, const std::string& text) :
		ListItem( name ),
		text( text ) {
	}	
	explicit TextListItem(const std::string& text) :
		TextListItem( "", text ) {
	}
	virtual ~TextListItem() {
	}
	
	/** @name IEntity implementations
	 */
	///@{ 	
	virtual std::string getType() const { return "TextListItem"; }
	///@}
	
public:
	static std::shared_ptr<TextListItem> make(const std::string& name, const std::string& text) {
		return std::make_shared<TextListItem>( name, text );
	}	
	static std::shared_ptr<TextListItem> make(const std::string& text) {
		return std::make_shared<TextListItem>( text );
	}
	
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


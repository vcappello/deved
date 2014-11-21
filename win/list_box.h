/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_LIST_BOX_H
#define WIN_LIST_BOX_H
 
#include <win/control.h>
#include <win/property.h>
#include <win/font.h>
#include <win/entity_vector.h>
#include <win/list_item.h>

namespace win {

class ListBox : public Control {
public:
	using ListItemsType = std::initializer_list<std::shared_ptr<win::ListItem>>;

public:
	ListBox(const std::string& name, int left, int top, int width, int height, ListItemsType initList) :
		Control( name ),
		left( left ),
		top( top ),
		width( width ),
		height( height ),
		visible( true ),
		enabled( true ),
		listItems( initList ) {
	}
	ListBox(const std::string& name, int left, int top, int width, int height) :
		ListBox( name, left, top, width, height, ListItemsType{ } ) {
	}
	ListBox(int left, int top, int width, int height, ListItemsType initList) :
		ListBox( "", left, top, width, height, initList ) {
	}	
	ListBox(int left, int top, int width, int height) :
		ListBox( "", left, top, width, height, ListItemsType{ } ) {
	}	
	ListBox() :
		ListBox( 0, 0, 0, 0 ) {
	}
	virtual ~ListBox() {
	}
	
	/** @name IEntity implementations
	 */
	///@{ 
	virtual std::string getType() const { return "ListBox"; }
	///@}
	
public:
	/** @name Properties
	 */
	///@{ 
	Property<int> left;
	Property<int> top;
	Property<int> width;
	Property<int> height;	
	Property<bool> visible;
	Property<bool> enabled;
	Property<std::shared_ptr<Font>> font;
	EntityVector<ListItem> listItems;
	Property<std::shared_ptr<ListItem>> selectedItem;
	///@}

	/** @name Events
	 */
	///@{ 
	///@}
};

}
 
#endif //  WIN_LIST_BOX_H
 
 
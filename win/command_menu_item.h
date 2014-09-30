/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */
 
#ifndef WIN_COMMAND_MENU_ITEM_H
#define WIN_COMMAND_MENU_ITEM_H

#include <win/menu_item.h>

#include <string>

namespace win {

class CommandMenuItem : public MenuItem {
public:
	explicit CommandMenuItem(const std::string& name) :
		MenuItem( name ),
		enabled( true ) {
	}
	CommandMenuItem(const std::string& name, const std::string& text) :
		MenuItem( name ),
		text( text ),
		enabled( true ) {
	}	
	virtual ~CommandMenuItem() {
	}
	
	// Control implementations	
	virtual std::string getType() const { return "CommandMenuItem"; } 
	
public:
	Property<std::string> text;
	Property<bool> enabled;

	Event<> clickedEvent;
};

}
 
#endif // WIN_COMMAND_MENU_ITEM_H
 
 
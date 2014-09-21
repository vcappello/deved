/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */
 
#include <win/menu_item.h>

#ifndef WIN_COMMAND_MENU_ITEM_H
#define WIN_COMMAND_MENU_ITEM_H
 
namespace win {

class CommandMenuItem : public MenuItem {
public:
	explicit CommandMenuItem(const std::string& name) :
		MenuItem( name ) {
	}
	virtual ~CommandMenuItem() {
	}
	
	// Control implementations	
	virtual std::string getType() const { return "CommandMenuItem"; } 
	
public:
	Property<std::string> text;	
};

}
 
#endif // WIN_COMMAND_MENU_ITEM_H
 
 
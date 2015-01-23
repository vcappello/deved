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
	CommandMenuItem(const std::string& name, const std::string& text) :
		MenuItem( name ),
		text( text ),
		enabled( true ) {
	}	
	explicit CommandMenuItem(const std::string& text) :
		CommandMenuItem( "", text ) {
	}
	virtual ~CommandMenuItem() {
	}
	
	/** @name Entity implementations
	 */
	///@{ 
	virtual std::string getType() const { return "CommandMenuItem"; } 
	///@}

public:
	static std::shared_ptr<CommandMenuItem> make(const std::string& name, const std::string& text) {
		return std::make_shared<CommandMenuItem>( name, text );
	}	
	static std::shared_ptr<CommandMenuItem> make(const std::string& text) {
		return std::make_shared<CommandMenuItem>( text );
	}
	
public:
	/** @name Properties
	 */
	///@{
	Property<std::string> text;
	Property<bool> enabled;
	///@}

	/** @name Events
	 */
	///@{ 
	Event<> clickedEvent;
	///@}
};

}
 
#endif // WIN_COMMAND_MENU_ITEM_H
 
 
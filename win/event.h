/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

 
#ifndef WIN_EVENT_H
#define WIN_EVENT_H

#include <list>
#include <functional>
#include <algorithm>

namespace win
{

/**
 * Event delegate type, call all registered std::function when 
 * the event is fired.
 *
 * For example you can declare an event with an integer argument:
 *
 *     // Declare an event with an integer argument 
 *     Event<int> onIntEvent;
 *
 * Later you register an event handler, it can be a lambda:
 *
 *     // Handle integer event
 *     onIntEvent.add([&](int arg){ 
 *       std::cout << "The argument is: " << arg << std::endl;
 *     });
 *
 * Later you can fire the event giving desired argument value:
 *
 *     // Fire the event with the integer value 5
 *     onIntEvent.fire (5);
 */
template<typename...Arguments>
class Event
{
public:
	Event() {
	}
	virtual ~Event() {
	}
	
public:
	using handler_t = std::function<void(Arguments...)>;
	
	void fire(Arguments... parameters) {
		for(auto handler : registry)
			handler (parameters...);
	}
	
	void add(handler_t handler) {
		registry.push_back (handler);
	}
	
	void remove(handler_t handler) {
		auto handler_itor = std::find(registry.begin(), registry.end(), handler);
		if (handler_itor != registry.end())
			registry.erase (handler_itor);
	}
	
	void clear() {
		registry.clear();
	}
	
	bool hasSubscriptions() const { return !registry.empty(); }
	
protected:
	std::list<handler_t> registry;
};

}

#endif // WIN_EVENT_H

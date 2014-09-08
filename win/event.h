#ifndef WIN_EVENT_H
#define WIN_EVENT_H

#include <iostream>
#include <list>
#include <functional>

namespace win
{

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

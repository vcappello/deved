/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_ENTITY_MAP_H
#define WIN_ENTITY_MAP_H

#include <win/event.h>
#include <win/error.h>

#include <string>
#include <memory>
#include <map>
#include <algorithm>

namespace win {

/**
 * A generic container of IEntity inherited objects
 */
template<class T>
class EntityMap {
public:
	using childEntityT = std::shared_ptr<T>;
	using keyT = std::string;
	using containerT = std::map<std::string, childEntityT>;
	using iteratorT = typename containerT::iterator;
	using constIteratorT = typename containerT::const_iterator;

public:
	EntityMap() {
	}
	EntityMap(std::initializer_list<childEntityT> initList) {
		for (auto item : initList) {
			add (item);
		}
	}
	virtual ~EntityMap() {
	}
	
public:
	childEntityT& operator[](const keyT& key) {
		return mMap[key];
	}

	const childEntityT& operator[](const keyT& key) const {
		return const_cast<childEntityT>(mMap[key]);
	}
	
	void add(const childEntityT& value) {
		if (!mMap.insert (std::make_pair( value->getName(), value )).second) {
			throw Error( "An entity with the name '" + value->getName() + "' already exist" );
		}
		
		itemAddedEvent.fire (value);
	}
	
	void remove(const keyT& key) {
		childEntityT entity = mMap[key];
		itemRemovedEvent.fire (entity);

		mMap.erase (key);		
	}
	
	iteratorT begin() {
		return mMap.begin();
	}

	constIteratorT begin() const {
		return mMap.begin();
	}

	iteratorT end() {
		return mMap.end();
	}

	constIteratorT end() const {
		return mMap.end();
	}
	
public:
	Event<childEntityT> itemAddedEvent;
	Event<childEntityT> itemRemovedEvent;
	
protected:
	containerT mMap;
};

}

#endif // WIN_ENTITY_MAP_H


/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_ENTITY_VECTOR_H
#define WIN_ENTITY_VECTOR_H

#include <win/event.h>
#include <win/error.h>

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

namespace win {

/**
 * A generic vector of IEntity inherited objects
 */
template<class T>
class EntityVector {
public:
	using ChildEntityType = std::shared_ptr<T>;
	using ContainerType = std::vector<ChildEntityType>;
	using IteratorType = typename ContainerType::iterator;
	using ConstIteratorType = typename ContainerType::const_iterator;

public:
	EntityVector() {
	}
	EntityVector(std::initializer_list<ChildEntityType> initList) {
		for (auto item : initList) {
			add (item);
		}
	}
	virtual ~EntityVector() {
	}
	
public:
	ChildEntityType& operator[](int index) {
		return mContainer[index];
	}

	const ChildEntityType& operator[](int index) const {
		return mContainer[index];
	}
	
	ChildEntityType& operator[](const std::string& name) {
		auto itor = std::find_if (std::begin(mContainer), std::end(mContainer), [&](const ChildEntityType& child){
			return name == child->getName();
		});
		if (itor == std::end (mContainer))
			throw Error( "Item with name '" + name + "' does not exist" );
		return (*itor);
	}

	const ChildEntityType& operator[](const std::string& name) const {
		auto itor = std::find_if (std::begin(mContainer), std::end(mContainer), [&](const ChildEntityType& child){
			return name == child->getName();
		});
		if (itor == std::end (mContainer))
			throw Error( "Item with name '" + name + "' does not exist" );
		return (*itor);
	}
	
	void add(const ChildEntityType& value) {
		// TODO: check entity ID before add?
		mContainer.push_back (value);
		
		itemAddedEvent.fire (value);
	}
	
	void remove(int index) {
		ChildEntityType entity = mContainer[index];
		itemRemovedEvent.fire (entity);

		mContainer.erase (std::begin(mContainer) + index);
	}

	void remove(const ChildEntityType& entity) {
		auto itor = std::find_if (std::begin(mContainer), std::end(mContainer), [&](const ChildEntityType& child){
			return entity == child;
		});
		if (itor == std::end (mContainer))
			throw Error( "Can not remove item, instance not found" );

		remove (itor - std::begin(mContainer));
	}
	
	void remove(const std::string& name) {
		auto itor = std::find_if (std::begin(mContainer), std::end(mContainer), [&](const ChildEntityType& child){
			return name == child->getName();
		});
		if (itor == std::end (mContainer))
			throw Error( "Can not remove item, entity with name '" + name + "' does not exist" );

		remove (itor - std::begin(mContainer));
	}
	
	IteratorType begin() {
		return mContainer.begin();
	}

	ConstIteratorType begin() const {
		return mContainer.begin();
	}

	IteratorType end() {
		return mContainer.end();
	}

	ConstIteratorType end() const {
		return mContainer.end();
	}
	
public:
	Event<ChildEntityType> itemAddedEvent;
	Event<ChildEntityType> itemRemovedEvent;
	
protected:
	ContainerType mContainer;
};

}

#endif // WIN_ENTITY_VECTOR_H


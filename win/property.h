/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_PROPERTY_H
#define WIN_PROPERTY_H

#include <win/event.h>

#include <vector>
#include <algorithm>

namespace win {

/**
 * A simple property, fire the changedEvent event when the value change
 */	
template<class T>
class Property {
public:
	Property() {
	}
	explicit Property(const T& value) :
		mValue( value ) {
	}
		
	virtual ~Property() {
	}
	
public:	
	/**
     * Property getter
	 * @return the property value
	 */
    const T& operator()() const {
        return mValue;
    }

    T& operator()() {
        return mValue;
    }
	
	/**
     * Property setter, if the value change the changedEvent
	 * is fired.
	 * @param value the new property value
	 */
    void operator()(const T& value) {
		if (value != mValue) {
			mValue = value;
			changedEvent.fire();
		}
    }
	
public:
	/**
	 * Event fired when the property value is changed
	 */
	Event<> changedEvent;

protected:
	T mValue;
};

/**
 * An array of properties with type T
 */
template<class T>
class PropertyArray {
public:
	using childPropertyT = Property<T>;
	using containerT = std::vector<childPropertyT>;
	using iteratorT = typename containerT::iterator;
	using constIteratorT = typename containerT::const_iterator;

public:
	PropertyArray() {
	}
	PropertyArray(std::initializer_list<T> initList) {
		for (auto item : initList) {
			add (item);
		}
	}
	virtual ~PropertyArray() {
	}
	
public:
	childPropertyT& operator[](std::size_t index) {
		return mArray[index];
	}

	const childPropertyT& operator[](std::size_t index) const {
		return const_cast<childPropertyT>(mArray[index]);
	}
	
	void add(const T& value) {
		childPropertyT property;
		property() = value;
		mArray.push_back (property);
		
		itemAddedEvent.fire (value);
	}
	
	void remove(std::size_t index) {
		childPropertyT property = mArray[index];
		itemRemovedEvent.fire (property());

		mArray.erase (index);		
	}
	
	iteratorT begin() {
		return mArray.begin();
	}

	constIteratorT begin() const {
		return mArray.begin();
	}

	iteratorT end() {
		return mArray.end();
	}

	constIteratorT end() const {
		return mArray.end();
	}
	
public:
	Event<T> itemAddedEvent;
	Event<T> itemRemovedEvent;
	
protected:
	containerT mArray;
};

}

#endif // WIN_PROPERTY_H


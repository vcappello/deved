/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_PROPERTY_H
#define WIN_PROPERTY_H

#include <vector>

#include <win/event.h>

namespace win {

/**
 * A simple property, fire the onPropertyChanged event when the value change
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
     * Property setter, if the value change the onPropertyChanged
	 * is fired.
	 * @param value the new property value
	 */
    void operator()(const T& value) {
		if (value != mValue) {
			mValue = value;
			onPropertyChanged.fire();
		}
    }
	
public:
	/**
	 * Event fired when the property value is changed
	 */
	Event<> onPropertyChanged;

protected:
	T mValue;
};

/**
 * An array of properties with type T
 */
template<class T>
class PropertyArray {
public:
	PropertyArray() {
	}
	virtual ~PropertyArray() {
	}
	
public:
	typedef Property<T> childPropertyT;
	typedef std::vector<childPropertyT> containerT;
	typedef typename containerT::iterator iteratorT;
	typedef typename containerT::const_iterator constIteratorT;

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
		
		onPropertyAdded.fire (value);
	}
	
	void remove(std::size_t index) {
		childPropertyT property = mArray[index];
		onPropertyRemoved.fire (property());

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
	Event<T> onPropertyAdded;
	Event<T> onPropertyRemoved;
	
protected:
	containerT mArray;
};

}

#endif // WIN_PROPERTY_H


#ifndef WIN_PROPERTY_H
#define WIN_PROPERTY_H

#include <vector>

#include <win/event.h>

namespace win {

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
	
	/**
     * Getter
	 */
    const T& operator()() const {
        return mValue;
    }

	/**
     * Setter
	 */
    void operator()(const T& value) {
		if (value != mValue) {
			mValue = value;
			onPropertyChanged.fire();
		}
    }
	
public:
	Event<> onPropertyChanged;

protected:
	T mValue;
};

template<class T>
class PropertyArray {
public:
	Property() {
	}
	virtual ~Property() {
	}
	
public:
	typedef typename Property<T> child_property_t;

	child_property_t& operator[](std::size_t index) {
		return mArray[index];
	}

	const child_property_t& operator[](std::size_t index) {
		return mArray[index];
	}
	
	void add(const T& value) {
		child_property_t property;
		property() = value;
		mArray.push_back (property);
		property.onPropertyChanged.add (onChildPropertyChanged);
		
		onPropertyChanged.fire();
	}
	
	void remove(std::size_t index) {
		mArray[index].remove (onChildPropertyChanged);
		mArray.erase (index);
		
		onPropertyChanged.fire();
	}
	
public:
	Event<> onPropertyChanged;

protected:
	void onChildPropertyChanged() {
		onPropertyChanged.fire();
	}
	
protected:
	std::vector<child_property_t> mArray;
};

}

#endif // WIN_PROPERTY_H


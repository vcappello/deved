/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_WINDOW_LAYOUT_H
#define WIN_WIN32_WINDOW_LAYOUT_H

#include <win/point.h>
#include <win/size.h>

#include <memory>
#include <windows.h>

namespace win {

template<class T>
class ControlLayout {
public:
	ControlLayout(HWND hWnd, std::shared_ptr<T> entity) :
		mHWnd( hWnd ),
		mEntity( entity ) {
			
		mEntity->left.changedEvent.add([&]{
			Point point = getPosition();
			if (point.x != mEntity->left()) {
				point.x = mEntity->left();
				setPosition (point);
			}
		});	
		
		mEntity->top.changedEvent.add([&]{
			Point point = getPosition();
			if (point.y != mEntity->top()) {
				point.y = mEntity->top();
				setPosition (point);
			}
		});	
			
		mEntity->width.changedEvent.add([&]{
			Size size = getSize();
			if (size.width != mEntity->width()) {
				size.width = mEntity->width();
				setSize (size);
			}
		});		
		
		mEntity->height.changedEvent.add([&]{
			Size size = getSize();
			if (size.height != mEntity->height()) {
				size.height = mEntity->height();
				setSize (size);
			}
		});
			
	}
	
	virtual ~ControlLayout() {
	}

	virtual Point getPosition() {
		HWND hWndParent = ::GetParent(mHWnd);
		POINT position = {};

		::MapWindowPoints(mHWnd, hWndParent, &position, 1);
		
		return Point( position.x, position.y );			
	}
	
	virtual void setPosition(const Point& value) {
		::SetWindowPos(mHWnd, 0, 
			value.x, value.y, 0, 0, 
			SWP_NOZORDER | SWP_NOSIZE);		
	}

	virtual Size getSize() {
		RECT rect;
		::GetWindowRect (mHWnd, &rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		return Size( width, height );		
	}
	
	virtual void setSize(const Size& size) {
		::SetWindowPos(mHWnd, 0, 
			0, 0, size.width, size.height, 
			SWP_NOZORDER | SWP_NOMOVE);			
	}

protected:
	HWND mHWnd;
	std::shared_ptr<T> mEntity;
};

template<class T>
class WindowLayout : public ControlLayout<T> {
public:
	WindowLayout(HWND hWnd, std::shared_ptr<T> entity) : 
		ControlLayout<T>( hWnd, entity ) {
	}
	virtual ~WindowLayout() {
	}
	
	Point getPosition() {
		RECT rect;
		::GetWindowRect (ControlLayout<T>::mHWnd, &rect);
		
		return Point( rect.left, rect.top );
	}	
};

}

#endif // WIN_WIN32_WINDOW_LAYOUT_H

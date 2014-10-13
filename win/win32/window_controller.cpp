#include "window_controller.h"

namespace win {
	
WindowController::WindowController(HWND hWnd, std::shared_ptr<Window> window) :
	WindowBase( hWnd ),
	mWindow( window ),
	mDefaultId( -1 ) {
		
	mWindow->title.changedEvent.add([&]{
		if (getText() != mWindow->title()) {
			setText (mWindow->title());
		}
	});
	
	mWindow->left.changedEvent.add([&]{
		Point point = getPosition();
		if (point.x != mWindow->left()) {
			point.x = mWindow->left();
			setPosition (point);
		}
	});	
	
	mWindow->top.changedEvent.add([&]{
		Point point = getPosition();
		if (point.y != mWindow->top()) {
			point.y = mWindow->top();
			setPosition (point);
		}
	});	
		
	mWindow->width.changedEvent.add([&]{
		Size size = getSize();
		if (size.width != mWindow->width()) {
			size.width = mWindow->width();
			setSize (size);
		}
	});		
	
	mWindow->height.changedEvent.add([&]{
		Size size = getSize();
		if (size.height != mWindow->height()) {
			size.height = mWindow->height();
			setSize (size);
		}
	});
	
	mWindow->visible.changedEvent.add([&] {
		if (isVisible() != mWindow->visible()) {
			setVisible (mWindow->visible());
		}
	});
	
	mWindow->controls.itemAddedEvent.add([&] (std::shared_ptr<Control> control) {
		auto controller = createControl (shared_from_this(), control);
		mResources.insert (std::make_pair (control->getName(), controller));
	});
	
	mWindow->controls.itemRemovedEvent.add([&] (std::shared_ptr<Control> control) {
		auto object = mResources[control->getName()];
		mResources.erase (control->getName());
		object->destroy();
	});	
}

WindowController::~WindowController() {
}

void WindowController::setMenuBarController(std::shared_ptr<MenuBarController> menuBarController) {
	mMenuBarController = menuBarController;
	::SetMenu (mHWnd, mMenuBarController->getHMenu());
}

int WindowController::getDefaultId() const {
	return mDefaultId;
}

void WindowController::setDefaultId(int value) {
	mDefaultId = value;
	// Redraw window
	::InvalidateRect (mHWnd, NULL, TRUE);
}

bool WindowController::handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult) {
	
	switch (message) {
		case WM_ACTIVATE:
		{
			if (wParam == 0) {
				MessageLoop::getInstance().setActiveWindowHWnd (NULL);
			} else {
				MessageLoop::getInstance().setActiveWindowHWnd (mHWnd);
			}
			break;
		}
		case WM_SETTEXT:
		{
			std::string text( (LPCTSTR)lParam );
			mWindow->title(text);
			break;
		}
		case WM_WINDOWPOSCHANGED:
		{
			WINDOWPOS* windowPos = (WINDOWPOS*)lParam;
			if (!(windowPos->flags & SWP_NOSIZE)) {
				mWindow->width (windowPos->cx);
				mWindow->height (windowPos->cy);
			}
			if (!(windowPos->flags & SWP_NOMOVE)) {
				mWindow->left (windowPos->x);
				mWindow->top (windowPos->y);
			}
			break;
		}
		case WM_STYLECHANGED:
		{
			STYLESTRUCT* styleStruct = (STYLESTRUCT*)lParam;
			if ((styleStruct->styleOld & WS_VISIBLE) != (styleStruct->styleNew & WS_VISIBLE)) {
				mWindow->visible (styleStruct->styleNew & WS_VISIBLE);
			}
		}
		case WM_DESTROY:
		{
			WindowBase::destroy();		
			::PostQuitMessage(0);
			break;
		}
	}
	
	return false;
}

LRESULT WindowController::callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return ::DefWindowProc (hWnd, message, wParam, lParam);
}

Point WindowController::getPosition() {
	RECT rect;
	::GetWindowRect (mHWnd, &rect);
	
	return Point( rect.left, rect.top );
}

}


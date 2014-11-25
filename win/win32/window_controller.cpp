#include "window_controller.h"

#include "button_controller.h"

namespace win {
	
WindowController::WindowController(HWND hWnd, std::shared_ptr<Window> window) :
	WindowContainerBase( hWnd ),
	mWindow( window ),
	mLayout( hWnd, window ),
	mDefaultId( -1 ) {
		
	mWindow->title.changedEvent.add([&]{
		if (getText() != mWindow->title()) {
			setText (mWindow->title());
		}
	});
	
	mWindow->visible.changedEvent.add([&] {
		if (isVisible() != mWindow->visible()) {
			setVisible (mWindow->visible());
		}
	});

	mWindow->defaultButton.changedEvent.add([&] {
		updateDefaultButton();
	});
	
	mWindow->controls.itemAddedEvent.add([&] (std::shared_ptr<Control> control) {
		auto controller = createController (shared_from_this(), control);
		mResources.insert (std::make_pair (control.get(), controller));
	});
	
	mWindow->controls.itemRemovedEvent.add([&] (std::shared_ptr<Control> control) {
		auto object = mResources[control.get()];
		mResources.erase (control.get());
		object->destroy();
	});	
}

WindowController::~WindowController() {
}

void WindowController::setMenuBarController(std::shared_ptr<MenuBarController> menuBarController) {
	mMenuBarController = menuBarController;
	if (mMenuBarController) {
		// TODO: handle error
		::SetMenu (mHWnd, mMenuBarController->getHMenu());
	} else {
		// TODO: handle error
		::SetMenu (mHWnd, NULL);
	}
}

int WindowController::getDefaultButtonId() const {
	return mDefaultId;
}

void WindowController::updateDefaultButton() {
	if (mWindow->defaultButton()) {
		// Set new instance
		auto newDefaultButtonController = std::dynamic_pointer_cast<ButtonController>( findResourceById (mWindow->defaultButton().get()) );
		if (newDefaultButtonController && (mDefaultId != newDefaultButtonController->getCommandId())) {
			// Deselect previous default button
			if (mDefaultId != -1) {
				auto oldDefaultButtonController = std::dynamic_pointer_cast<ButtonController>( MessageDispatcher::getInstance().getControllerById (mDefaultId) );
				if (oldDefaultButtonController) {
					oldDefaultButtonController->setDefault (false);
				}
			}
			// Select new default button
			mDefaultId = newDefaultButtonController->getCommandId();
			newDefaultButtonController->setDefault (true);
			// Redraw window
			::InvalidateRect (mHWnd, NULL, TRUE);
		}
	} else {
		// Clear current instance
		if (mDefaultId != -1) {
			auto oldDefaultButtonController = std::dynamic_pointer_cast<ButtonController>( MessageDispatcher::getInstance().getControllerById (mDefaultId) );
			oldDefaultButtonController->setDefault (false);
			mDefaultId = -1;
			// Redraw window
			::InvalidateRect (mHWnd, NULL, TRUE);
		}
	}
}

bool WindowController::handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult) {
	
	switch (message) {
		case WM_CREATE:
		{
			std::shared_ptr<FontResource> fontResource;
			if (mWindow->font()) {
				fontResource = createFontResource (mWindow->font());
			} else {
				fontResource = createFontResource (getSystemFont());
			}
			setFontResource (fontResource);
			
			// Add owned controls
			for (auto control : mWindow->controls) {
				createController (shared_from_this(), control);
			}

			// Default button
			if (mWindow->defaultButton()) {
				updateDefaultButton();
			}			
			break;
		}
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

}


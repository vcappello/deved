#include "group_box_controller.h"
#include "message_dispatcher.h"

namespace win {
	
GroupBoxController::GroupBoxController(HWND hWnd, int commandId, std::shared_ptr<GroupBox> groupBox) :
	WindowContainerBase( hWnd ),
	mCommandId( commandId ),
	mGroupBox( groupBox ),
	mLayout( hWnd, groupBox ),
	mOldWndProc( NULL )	{
		
	mGroupBox->text.changedEvent.add([&]{
		if (getText() != mGroupBox->text()) {
			setText (mGroupBox->text());
		}
	});
	
	mGroupBox->visible.changedEvent.add([&] {
		if (isVisible() != mGroupBox->visible()) {
			setVisible (mGroupBox->visible());
		}
	});	

	mGroupBox->enabled.changedEvent.add([&] {
		if (isEnabled() != mGroupBox->enabled()) {
			setEnabled (mGroupBox->enabled());
		}
	});
	
	mGroupBox->controls.itemAddedEvent.add([&] (std::shared_ptr<Control> control) {
		auto controller = createController (shared_from_this(), control);
		mResources.insert (std::make_pair (control->getName(), controller));
	});
	
	mGroupBox->controls.itemRemovedEvent.add([&] (std::shared_ptr<Control> control) {
		auto object = mResources[control->getName()];
		mResources.erase (control->getName());
		object->destroy();
	});	
}

GroupBoxController::~GroupBoxController() {
	// Remove subclassing
	if (mOldWndProc) {
		SetWindowLongPtr (mHWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( mOldWndProc ));
	}
}

void GroupBoxController::subclass() {
	mOldWndProc = reinterpret_cast<WNDPROC>( 
		SetWindowLongPtr (mHWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( 
			MessageDispatcher::uniqueWndProc )) );
}

bool GroupBoxController::handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult) {
	bool handled = false;
	switch (message) {
		case WM_SETTEXT:
		{
			std::string text( reinterpret_cast<LPCTSTR>( lParam ));
			mGroupBox->text(text);
			break;
		}
		case WM_ERASEBKGND:
		{
			RECT    rect;

			HDC hDC = reinterpret_cast<HDC>(wParam);

			// Erase the group box's background.
			::GetClientRect (mHWnd, &rect);
			::FillRect (hDC, &rect, reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1));

			lResult = TRUE;
			handled = true;
			break;
		}
		case WM_SETFONT:
		{
			HFONT hFont = reinterpret_cast<HFONT>( wParam );
			if (hFont != getFontResource()->getHFont()) {
				LOGFONT logFont;
				::GetObject (hFont, sizeof(logFont), &logFont);
				getFontResource()->updateModelFromLogFont (logFont);
			}
			break;
		}
		case WM_WINDOWPOSCHANGED:
		{
			WINDOWPOS* windowPos = reinterpret_cast<WINDOWPOS*>( lParam );
			if (!(windowPos->flags & SWP_NOSIZE)) {
				mGroupBox->width (windowPos->cx);
				mGroupBox->height (windowPos->cy);
			}
			if (!(windowPos->flags & SWP_NOMOVE)) {
				mGroupBox->left (windowPos->x);
				mGroupBox->top (windowPos->y);
			}
			break;
		}
		case WM_STYLECHANGED:
		{
			STYLESTRUCT* styleStruct = reinterpret_cast<STYLESTRUCT*>( lParam );
			if ((styleStruct->styleOld & WS_DISABLED) != (styleStruct->styleNew & WS_DISABLED)) {
				mGroupBox->enabled (!(styleStruct->styleNew & WS_DISABLED));
			}
			if ((styleStruct->styleOld & WS_VISIBLE) != (styleStruct->styleNew & WS_VISIBLE)) {
				mGroupBox->visible (styleStruct->styleNew & WS_VISIBLE);
			}
		}		
	}
	return handled;
}

LRESULT GroupBoxController::callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return ::CallWindowProc (mOldWndProc, hWnd, message, wParam, lParam);
}

void GroupBoxController::handleCommand(WPARAM wParam, LPARAM lParam) {
	//~ int notification = HIWORD(wParam);
	//~ switch (notification) {
		//~ case BN_CLICKED:
		//~ {
			//~ mGroupBox->clickedEvent.fire();
		//~ }
	//~ }
}

}


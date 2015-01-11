#include "group_box_controller.h"

namespace win {
	
GroupBoxController::GroupBoxController(HWND hWnd, int commandId, std::shared_ptr<GroupBox> groupBox) :
	WindowContainerBase( hWnd ),
	mCommandId( commandId ),
	mGroupBox( groupBox ),
	mLayout( hWnd, groupBox ) {
		
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
		mResources.insert (std::make_pair (control.get(), controller));
	});
	
	mGroupBox->controls.itemRemovedEvent.add([&] (std::shared_ptr<Control> control) {
		auto object = mResources[control.get()];
		mResources.erase (control.get());
		object->destroy();
	});	
}

GroupBoxController::~GroupBoxController() {
}

void GroupBoxController::subclass() {
	mSubclassHandler = SubclassHandler::create (mHWnd);
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
			getFontResource()->setHFont (hFont);
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
	if (mSubclassHandler) {
		return mSubclassHandler->callDefWindowProc (hWnd, message, wParam, lParam);
	}
	return 0;
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


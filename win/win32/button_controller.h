/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_BUTTON_CONTROLLER_H
#define WIN_WIN32_BUTTON_CONTROLLER_H

#include <win/button.h>
#include "window_base.h"
#include "i_notification_handler.h"
#include "window_layout.h"
#include "subclass_handler.h"
#include "gdi_object.h"

#include <memory>
#include <windows.h>

namespace win {

class ButtonController : public WindowBase, 
                         public INotificationHandler {
public:
	ButtonController(HWND hWnd, int commandId, std::shared_ptr<Button> button);
	virtual ~ButtonController();

	std::shared_ptr<Button> getButton() { return mButton; }

	bool isDefault();
	void setDefault(bool value);
	
	void subclass();
	
	/** @name IMessageHandler implementations
	 */
	///@{ 	
	// HWND getHWnd() { return mHWnd; } // Implemented on WindowBase
	
	bool handleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult);

	LRESULT callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	///@}
	
	/** @name INotificationHandler implementations
	 */
	///@{ 	
	int getCommandId() const { return mCommandId; }
	
	void handleCommand(WPARAM wParam, LPARAM lParam);
	///@}
	
protected:
	int mCommandId;
	std::shared_ptr<Button> mButton;
	ControlLayout<Button> mLayout;
	std::unique_ptr<SubclassHandler> mSubclassHandler;
	std::unique_ptr<GdiObject<HBRUSH>> mBackgroundBrush;
};

}

#endif // WIN_WIN32_BUTTON_CONTROLLER_H

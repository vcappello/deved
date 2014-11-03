/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_LABEL_CONTROLLER_H
#define WIN_WIN32_LABEL_CONTROLLER_H

#include <win/label.h>
#include "window_base.h"
#include "i_notification_handler.h"
#include "window_layout.h"
#include "subclass_handler.h"

#include <memory>
#include <windows.h>

namespace win {

class LabelController : public WindowBase, 
                       public INotificationHandler {
public:
	LabelController(HWND hWnd, int commandId, std::shared_ptr<Label> label);
	virtual ~LabelController();

	std::shared_ptr<Label> getLabel() { return mLabel; }

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
	std::shared_ptr<Label> mLabel;
	ControlLayout<Label> mLayout;
	std::unique_ptr<SubclassHandler> mSubclassHandler;
};

}

#endif // WIN_WIN32_LABEL_CONTROLLER_H

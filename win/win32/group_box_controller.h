/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_GROUP_BOX_CONTROLLER_H
#define WIN_WIN32_GROUP_BOX_CONTROLLER_H

#include <win/group_box.h>
#include "window_container_base.h"
#include "i_notification_handler.h"
#include "window_layout.h"
#include "control_factory.h"

#include <memory>
#include <windows.h>

namespace win {

class GroupBoxController : public WindowContainerBase, 
                           public INotificationHandler,
                           public std::enable_shared_from_this<GroupBoxController> {
public:
	explicit GroupBoxController(HWND hWnd, int commandId, std::shared_ptr<GroupBox> groupBox);
	virtual ~GroupBoxController();

	std::shared_ptr<GroupBox> getGroupBox() { return mGroupBox; }

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
	std::shared_ptr<GroupBox> mGroupBox;
	ControlLayout<GroupBox> mLayout;
	WNDPROC mOldWndProc;
};

}

#endif // WIN_WIN32_GROUP_BOX_CONTROLLER_H

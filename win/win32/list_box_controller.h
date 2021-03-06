/**
 * (c) 2014 Vincenzo Cappello
 * This projected is licensed under the terms of the MIT license, 
 * refer to the file LICENSE.txt.
 */

#ifndef WIN_WIN32_LIST_BOX_CONTROLLER_H
#define WIN_WIN32_LIST_BOX_CONTROLLER_H

#include <win/list_box.h>
#include <win/error.h>
#include "window_base.h"
#include "i_notification_handler.h"
#include "window_layout.h"
#include "subclass_handler.h"
#include "list_item_controller.h"
#include "gdi_object.h"

#include <memory>
#include <windows.h>

namespace win {

class ListBoxController : public WindowBase, 
                          public INotificationHandler,
                          public std::enable_shared_from_this<ListBoxController> {
public:
	using listItemKeyT = ListItem*;
	
public:
	ListBoxController(HWND hWnd, int commandId, std::shared_ptr<ListBox> listBox);
	virtual ~ListBoxController();

	std::shared_ptr<ListBox> getListBox() { return mListBox; }
	
	void addListItemController(std::shared_ptr<ListItemController> listItemController);
	
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
	std::shared_ptr<ListBox> mListBox;
	ControlLayout<ListBox> mLayout;
	std::unique_ptr<SubclassHandler> mSubclassHandler;
	std::map<listItemKeyT, std::shared_ptr<ListItemController>> mListItemControllers;
	std::unique_ptr<GdiObject<HBRUSH>> mBackgroundBrush;

protected:
	int getCurrentSelection();
	int getItemsCount();
	listItemKeyT getItemKey(int index);

	void rebuildIndexes();
};

}

#endif // WIN_WIN32_LIST_BOX_CONTROLLER_H

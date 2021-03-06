#include "control_factory.h"

#include "window_controller.h"
#include "button_controller.h"
#include "edit_controller.h"
#include "label_controller.h"
#include "group_box_controller.h"
#include "list_box_controller.h"
#include "menu_bar_controller.h"
#include "command_menu_item_controller.h"
#include "sub_menu_item_controller.h"
#include "message_dispatcher.h"
#include "font_resource.h"
#include "list_item_factory.h"

namespace win {

int createControlId() {
	static int controlIdCounter = 100;
	return controlIdCounter++;
}
	
template<class T>
std::shared_ptr<T> castControl(std::shared_ptr<Control> control) {
	auto castedControl = std::dynamic_pointer_cast<T>(control);
	if (!castedControl) {
		throw Error( "Can not create control '" + control->name() + "'" );
	}
	return castedControl;
}

class ButtonClass {
public:
	using ControllerType = ButtonController;

	static const char* getClassName() { return "BUTTON"; }
	
	static std::tuple<DWORD,DWORD> getStyle(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<Button> button) {
		DWORD window_style_ex = 0;
		DWORD window_style = WS_TABSTOP | WS_CHILD;
		
		auto windowController = findWindowControllerFromChild (windowContainer);
		if (windowController && windowController->getWindow()->defaultButton() == button) {
			window_style |= BS_DEFPUSHBUTTON;
		}
		if (!button->enabled()) {
			window_style |= WS_DISABLED;
		}
		if (button->visible()) {
			window_style |= WS_VISIBLE;
		}
		
		return std::make_tuple (window_style, window_style_ex);
	}
};

std::shared_ptr<WindowsObject> createController(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<Control> control) {
	std::shared_ptr<WindowsObject> object;
	if (control->getType() == "Button") {
		auto buttonControl = castControl<Button>(control);
		object = createButtonController (windowContainer, buttonControl);
	} else if (control->getType() == "Edit") {
		auto editControl = castControl<Edit>(control);
		object = createEditController (windowContainer, editControl);
	} else if (control->getType() == "Label") {
		auto labelControl = castControl<Label>(control);
		object = createLabelController (windowContainer, labelControl); 
	} else if (control->getType() == "GroupBox") {
		auto groupBoxControl = castControl<GroupBox>(control);
		object = createGroupBoxController (windowContainer, groupBoxControl);
	} else if (control->getType() == "ListBox") {
		auto listBoxControl = castControl<ListBox>(control);
		object = createListBoxController (windowContainer, listBoxControl);		
	} else if (control->getType() == "MenuBar") {
		auto menuBarControl = castControl<MenuBar>(control);
		object = createMenuBarController (windowContainer, menuBarControl);
	} else {
		throw Error( "Can not create control '" + control->name() + "' unknown type '" + control->getType() + "'" );
	}
	return object;
}

std::shared_ptr<ButtonController> createButtonController(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<Button> button) {
	HINSTANCE hInstance = ::GetModuleHandle(NULL);

	DWORD window_style_ex = 0;
	DWORD window_style = 0;
	
	std::tie( window_style, window_style_ex ) = ButtonClass::getStyle(windowContainer, button);
	
	int controlId = createControlId();
	HWND hWnd = CreateWindowEx (
					window_style_ex,
	                ButtonClass::getClassName(),
	                button->text().c_str(),
	                window_style,
					button->left(),
					button->top(),
					button->width(),
					button->height(),
	                windowContainer->getHWnd(),
	                (HMENU)(intptr_t)controlId,
	                hInstance,
	                NULL);

	if (!hWnd) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}	
	
	// Create ButtonController instance
	auto controller = std::make_shared<ButtonClass::ControllerType>( hWnd, controlId, button );
	MessageDispatcher::getInstance().registerController (controller);

	// Initialize font
	std::shared_ptr<FontResource> fontResource;
	if (button->font()) {
		fontResource = createFontResource (button->font());
	} else {
		fontResource = createFontResource (getSystemFont());
	}
	controller->setFontResource (fontResource);
	
	// Add the control to the container window
	windowContainer->addChildWindow (button.get(), controller);
	
	// Subclass window
	controller->subclass();
	
	return controller;
}

std::shared_ptr<EditController> createEditController(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<Edit> edit) {
	HINSTANCE hInstance = ::GetModuleHandle(NULL);

	DWORD window_style_ex = 0;
	DWORD window_style = WS_TABSTOP | WS_CHILD | ES_AUTOHSCROLL;
	
	if (edit->multiline()) {
		window_style |= ES_MULTILINE;
	}
	if (!edit->enabled()) {
		window_style |= WS_DISABLED;
	}
	if (edit->visible()) {
		window_style |= WS_VISIBLE;
	}
	if (edit->border()) {
		window_style_ex |= WS_EX_CLIENTEDGE;
	}
	
	int controlId = createControlId();
	HWND hWnd = CreateWindowEx (
					window_style_ex,
	                "EDIT",
	                edit->text().c_str(),
	                window_style,
					edit->left(),
					edit->top(),
					edit->width(),
					edit->height(),
	                windowContainer->getHWnd(),
	                (HMENU)(intptr_t)controlId,
	                hInstance,
	                NULL);

	if (!hWnd) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}	
	
	// Create EditController instance
	auto controller = std::make_shared<EditController>( hWnd, controlId, edit );
	MessageDispatcher::getInstance().registerController (controller);
	
	// Initialize font
	std::shared_ptr<FontResource> fontResource;
	if (edit->font()) {
		fontResource = createFontResource (edit->font());
	} else {
		fontResource = createFontResource (getSystemFont());
	}
	controller->setFontResource (fontResource);

	// Add the control to the container window
	windowContainer->addChildWindow (edit.get(), controller);
	
	// Subclass window
	controller->subclass();
	
	return controller;	
}

std::shared_ptr<LabelController> createLabelController(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<Label> label) {
	HINSTANCE hInstance = ::GetModuleHandle(NULL);

	DWORD window_style_ex = 0;
	DWORD window_style = WS_TABSTOP | WS_CHILD | ES_AUTOHSCROLL;
	
	if (!label->enabled()) {
		window_style |= WS_DISABLED;
	}
	if (label->visible()) {
		window_style |= WS_VISIBLE;
	}
	if (label->border()) {
		window_style_ex |= WS_EX_CLIENTEDGE;
	}
	
	int controlId = createControlId();
	HWND hWnd = CreateWindowEx (
					window_style_ex,
	                "STATIC",
	                label->text().c_str(),
	                window_style,
					label->left(),
					label->top(),
					label->width(),
					label->height(),
	                windowContainer->getHWnd(),
	                (HMENU)(intptr_t)controlId,
	                hInstance,
	                NULL);

	if (!hWnd) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}	
	
	// Create EditController instance
	auto controller = std::make_shared<LabelController>( hWnd, controlId, label );
	MessageDispatcher::getInstance().registerController (controller);
	
	// Initialize font
	std::shared_ptr<FontResource> fontResource;
	if (label->font()) {
		fontResource = createFontResource (label->font());
	} else {
		fontResource = createFontResource (getSystemFont());
	}
	controller->setFontResource (fontResource);

	// Add the control to the container window
	windowContainer->addChildWindow (label.get(), controller);
	
	// Subclass window
	controller->subclass();
	
	return controller;	
}

std::shared_ptr<GroupBoxController> createGroupBoxController(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<GroupBox> groupBox) {
	HINSTANCE hInstance = ::GetModuleHandle(NULL);

	DWORD window_style_ex = WS_EX_CONTROLPARENT; // For allow the TAB key to iterate over children controls
	DWORD window_style = WS_CHILD | WS_TABSTOP | BS_GROUPBOX;
	
	if (!groupBox->enabled()) {
		window_style |= WS_DISABLED;
	}
	if (groupBox->visible()) {
		window_style |= WS_VISIBLE;
	}
	
	int controlId = createControlId();
	HWND hWnd = CreateWindowEx (
					window_style_ex,
	                "BUTTON",
	                groupBox->text().c_str(),
	                window_style,
					groupBox->left(),
					groupBox->top(),
					groupBox->width(),
					groupBox->height(),
	                windowContainer->getHWnd(),
	                (HMENU)(intptr_t)controlId,
	                hInstance,
	                NULL);

	if (!hWnd) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}	
	
	// Create GroupBoxController instance
	auto controller = std::make_shared<GroupBoxController>( hWnd, controlId, groupBox );
	MessageDispatcher::getInstance().registerController (controller);

	// Initialize font
	std::shared_ptr<FontResource> fontResource;
	if (groupBox->font()) {
		fontResource = createFontResource (groupBox->font());
	} else {
		fontResource = createFontResource (getSystemFont());
	}
	controller->setFontResource (fontResource);
	
	// Add the control to the container window
	windowContainer->addChildWindow (groupBox.get(), controller);
	
	// Add owned controls
	for (auto control : groupBox->controls) {
		createController (controller, control);
	}
	
	// Subclass window
	controller->subclass();
	
	return controller;	
}

std::shared_ptr<ListBoxController> createListBoxController(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<ListBox> listBox) {
	HINSTANCE hInstance = ::GetModuleHandle(NULL);

	DWORD window_style_ex = WS_EX_CLIENTEDGE;
	DWORD window_style = WS_CHILD | WS_TABSTOP | WS_VSCROLL | LBS_NOTIFY;
	
	if (!listBox->enabled()) {
		window_style |= WS_DISABLED;
	}
	if (listBox->visible()) {
		window_style |= WS_VISIBLE;
	}
	
	int controlId = createControlId();
	HWND hWnd = CreateWindowEx (
					window_style_ex,
	                "LISTBOX",
	                NULL,
	                window_style,
					listBox->left(),
					listBox->top(),
					listBox->width(),
					listBox->height(),
	                windowContainer->getHWnd(),
	                (HMENU)(intptr_t)controlId,
	                hInstance,
	                NULL);

	if (!hWnd) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}	
	
	// Create GroupBoxController instance
	auto controller = std::make_shared<ListBoxController>( hWnd, controlId, listBox );
	MessageDispatcher::getInstance().registerController (controller);

	// Initialize font
	std::shared_ptr<FontResource> fontResource;
	if (listBox->font()) {
		fontResource = createFontResource (listBox->font());
	} else {
		fontResource = createFontResource (getSystemFont());
	}
	controller->setFontResource (fontResource);
	
	// Add the control to the container window
	windowContainer->addChildWindow (listBox.get(), controller);
	
	// Add list items
	for (auto listItem : listBox->listItems) {
		auto listItemController = createListItemController (controller, listItem);
		controller->addListItemController (listItemController);
	}
	
	// Subclass window
	controller->subclass();
	
	return controller;		
}

std::shared_ptr<MenuBarController> createMenuBarController(std::shared_ptr<WindowContainerBase> windowContainer, std::shared_ptr<MenuBar> menuBar) {
	auto controller = std::make_shared<MenuBarController>( menuBar );
	
	// Create children menu items	
	for (auto menuItem : menuBar->menuItems) {
		createMenuItemController (controller, menuItem);
	}
	
	auto windowController = findWindowControllerFromChild (windowContainer);
	if (windowController) {
		windowController->setMenuBarController (controller);
	}
	
	return controller;
}

std::shared_ptr<MenuItemControllerBase> createMenuItemController(std::shared_ptr<IMenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<MenuItem> menuItem) {
	std::shared_ptr<MenuItemControllerBase> menuItemControllerBase;
	if (menuItem->getType() == "CommandMenuItem") {
		
		auto commandMenuItem = std::dynamic_pointer_cast<CommandMenuItem>(menuItem);
		if (!commandMenuItem) {
			throw Error( "Can not convert control to 'CommandMenuItem'" );
		}			
		menuItemControllerBase = createCommandMenuItemController (menuItemControllerContainer, commandMenuItem);
		
	} else if (menuItem->getType() == "SubMenuItem") {
		
		auto subMenuItem = std::dynamic_pointer_cast<SubMenuItem>(menuItem);
		if (!subMenuItem) {
			throw Error( "Can not convert control to 'SubMenuItem'" );
		}				
		menuItemControllerBase = createSubMenuItemController (menuItemControllerContainer, subMenuItem);
		
	}
	
	return menuItemControllerBase;
}

std::shared_ptr<CommandMenuItemController> createCommandMenuItemController(std::shared_ptr<IMenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<CommandMenuItem> commandMenuItem) {
	// Get a new control ID for the menu item
	int controlId = createControlId();
	
	// Fill MENUITEMINFO structure
	MENUITEMINFO mii = {};
	mii.cbSize = sizeof(MENUITEMINFO);

	mii.fMask = MIIM_STRING | MIIM_ID | MIIM_FTYPE; 
    mii.fType = MFT_STRING;
	mii.wID = controlId;
    mii.dwTypeData = (LPSTR)commandMenuItem->text().c_str();
	mii.cch = commandMenuItem->text().size();
	
	if (!commandMenuItem->enabled()) {
		mii.fState = MFS_DISABLED;
		mii.fMask |= MIIM_STATE;
	}
	
	// Insert the new item as last item of the parent container	
	int position = ::GetMenuItemCount(menuItemControllerContainer->getHMenu());
	BOOL res = ::InsertMenuItem(menuItemControllerContainer->getHMenu(), position, TRUE, &mii); 	
	
	if (!res) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}

	auto controller = std::make_shared<CommandMenuItemController>( menuItemControllerContainer->getHMenu(), controlId, commandMenuItem );
	
	// Add menu item to the parent container
	menuItemControllerContainer->addMenuItem (controller);

	// Register the controller for notifications handling
	MessageDispatcher::getInstance().registerController (controller);
	
	return controller;
}

std::shared_ptr<SubMenuItemController> createSubMenuItemController(std::shared_ptr<IMenuItemControllerContainer> menuItemControllerContainer, std::shared_ptr<SubMenuItem> subMenuItem) {
	// Get a new control ID for the menu item
	int controlId = createControlId();

	// First create the controller since we need an HMENU
	auto controller = std::make_shared<SubMenuItemController>( menuItemControllerContainer->getHMenu(), controlId, subMenuItem );

	// Fill MENUITEMINFO structure
	MENUITEMINFO mii = {};
	mii.cbSize = sizeof(MENUITEMINFO);

	mii.fMask = MIIM_STRING | MIIM_ID | MIIM_FTYPE | MIIM_SUBMENU; 
    mii.fType = MFT_STRING;
	mii.wID = controlId;
    mii.dwTypeData = (LPSTR)subMenuItem->text().c_str();
	mii.cch = subMenuItem->text().size();
	mii.hSubMenu = controller->getHMenu();
	
	// Insert the new item as last item of the parent container
	int position = ::GetMenuItemCount(menuItemControllerContainer->getHMenu());
	BOOL res = ::InsertMenuItem(menuItemControllerContainer->getHMenu(), position, TRUE, &mii); 	
	
	if (!res) {
		throw Error( formatSystemMessage (::GetLastError()) );
	}
	
	// Add menu item to the parent container
	menuItemControllerContainer->addMenuItem (controller);
	
	// Create children menu items
	for (auto menuItem : subMenuItem->menuItems) {
		createMenuItemController (controller, menuItem);
	}
	
	return controller;
}

std::shared_ptr<WindowController> createWindowController(HWND hWnd, std::shared_ptr<Window> window) {
	auto controller = std::make_shared<WindowController>( hWnd, window );
	MessageDispatcher::getInstance().registerController (controller);
	
	return controller;
}

std::shared_ptr<WindowController> findWindowControllerFromChild(std::shared_ptr<WindowBase> childController) {
	auto windowController = std::dynamic_pointer_cast<WindowController>( childController );
	if (windowController) {
		return windowController; 
	}
	
	HWND hWndRoot = ::GetAncestor( childController->getHWnd(), GA_ROOT );
	if (!hWndRoot) {
		return nullptr;
	}
	
	windowController = std::dynamic_pointer_cast<WindowController>( MessageDispatcher::getInstance().getControllerByHandle(hWndRoot) );
	if (windowController) {
		return windowController; 
	}
	
	return nullptr;
}

HFONT createHFont(std::shared_ptr<Font> font) {
	LOGFONT logFont;
	logFont = {};
	
	std::copy (font->fontName().begin(), font->fontName().end(), logFont.lfFaceName);
	
	HDC hDC = ::GetDC(0);
	logFont.lfHeight = -MulDiv(font->size(), ::GetDeviceCaps(hDC, LOGPIXELSY), 72);
	
	logFont.lfWeight = font->bold() ? FW_BOLD : FW_NORMAL;
	logFont.lfItalic = font->italic() ? TRUE : FALSE;
	logFont.lfUnderline = font->underline() ? TRUE : FALSE;
	
	HFONT hFont = ::CreateFontIndirect (&logFont);
	if (!hFont) {
		throw Error( "Error creating font" );
	}

	return hFont;
}

std::shared_ptr<Font> createFont(const LOGFONT& logFont) {
	HDC hDC = ::GetDC(0);
	
	int size = -MulDiv(72, logFont.lfHeight, ::GetDeviceCaps(hDC, LOGPIXELSY));
	
	bool bold = (logFont.lfWeight > FW_NORMAL);
	bool italic = (logFont.lfItalic != false);
	bool underline = (logFont.lfUnderline != false);

	auto font = std::make_shared<Font>(
		logFont.lfFaceName, size, bold, italic, underline );
	
	return font;	
}

std::shared_ptr<FontResource> createFontResource(std::shared_ptr<Font> font) {
	HFONT hFont = createHFont (font);
	
	auto fontResource = std::make_shared<FontResource>( hFont, font );
	
	return fontResource;
}

}



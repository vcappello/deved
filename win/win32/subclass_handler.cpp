#include "subclass_handler.h"

#include "message_dispatcher.h"

namespace win {

SubclassHandler::SubclassHandler(HWND hWnd) :
	mHWnd( hWnd ) {
	mOldWndProc = reinterpret_cast<WNDPROC>( 
		::SetWindowLongPtr (mHWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( 
			MessageDispatcher::uniqueWndProc )) );
}

SubclassHandler::~SubclassHandler() {
	// Remove subclassing
	if (mOldWndProc) {
		::SetWindowLongPtr (mHWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( mOldWndProc ));
	}	
}

LRESULT SubclassHandler::callDefWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return ::CallWindowProc (mOldWndProc, hWnd, message, wParam, lParam);
}

std::unique_ptr<SubclassHandler> SubclassHandler::create(HWND hWnd) {
	return std::unique_ptr<SubclassHandler>( new SubclassHandler( hWnd ) );
}

}


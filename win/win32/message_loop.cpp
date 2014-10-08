#include "message_loop.h"

namespace win {
	
MessageLoop::MessageLoop() :
	mActiveWindowHWnd( NULL ) {
}

MessageLoop::~MessageLoop() {
}

MessageLoop& MessageLoop::getInstance() {
	static MessageLoop instance;
	
	return instance;
}

void MessageLoop::setActiveWindowHWnd (HWND hWnd) {
	mActiveWindowHWnd = hWnd;
}

int MessageLoop::start() {

    MSG msg;
	BOOL ret;
	
    while ((ret = ::GetMessage (&msg, NULL, 0, 0)) != 0)
    {
		if (ret == -1) {
			// TODO: handle the error and possibly exit
		} else {
			if (mActiveWindowHWnd != NULL) {
				if(!::IsDialogMessage (mActiveWindowHWnd,&msg))
				{
					::TranslateMessage (&msg);
					::DispatchMessage (&msg);
				}		
			} else {
				::TranslateMessage (&msg);
				::DispatchMessage (&msg);
			}
		}
    }

    return static_cast<int>( msg.wParam );
}

}


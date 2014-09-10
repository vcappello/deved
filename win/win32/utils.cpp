#include "utils.h"

namespace win {
	
std::string formatSystemMessage(DWORD code) {
	std::string message;

	LPTSTR msg_text = NULL;

	FormatMessage(
	    FORMAT_MESSAGE_FROM_SYSTEM
	    | FORMAT_MESSAGE_ALLOCATE_BUFFER
	    | FORMAT_MESSAGE_IGNORE_INSERTS,
	    NULL,
	    code,
	    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	    (LPTSTR)&msg_text,
	    0,
	    NULL);

	if (msg_text != NULL) {
		message = msg_text;

		// release memory allocated by FormatMessage()
		LocalFree(msg_text);
		msg_text = NULL;
	}

	return message;	
}
	
}

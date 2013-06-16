#ifndef LIBCOMMON_KEYUPMESSAGE_H
#define LIBCOMMON_KEYUPMESSAGE_H
#include "InputMessage.h"
namespace LibCommon {
	class KeyUpMessage : public InputMessage {
		KeyUpMessage::KeyUpMessage(std::wstring action);
	};
}

#endif
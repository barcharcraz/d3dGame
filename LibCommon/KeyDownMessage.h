#ifndef LIBCOMMON_KEYDOWNMESSAGE_H
#define LIBCOMMON_KEYDOWNMESSAGE_H
#include "InputMessage.h"
#include <string>

namespace LibCommon {
	class KeyDownMessage : public InputMessage {
		KeyDownMessage(std::wstring action);
	};
}
#endif
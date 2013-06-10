#ifndef LIBCOMMON_INPUTMESSAGE_H
#define LIBCOMMON_INPUTMESSAGE_H

#include "IMessage.h"
#include <string>

namespace LibCommon {
	class InputMessage : public IMessage {
	public:
		InputMessage(std::wstring action);
		std::wstring action;
	};
}

#endif
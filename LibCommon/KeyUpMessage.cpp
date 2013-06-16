#include "stdafx.h"
#include "KeyUpMessage.h"

namespace LibCommon {
	KeyUpMessage::KeyUpMessage(std::wstring action)
		: InputMessage(action) {
	}
}
#include "stdafx.h"
#include "KeyDownMessage.h"

namespace LibCommon {
	KeyDownMessage::KeyDownMessage(std::wstring action)
		: InputMessage(action) {
	}
}
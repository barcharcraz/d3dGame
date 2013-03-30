#ifndef LIBCOMMON_IMESSAGE_H
#define LIBCOMMON_IMESSAGE_H
#include "IComponent.h"

namespace LibCommon {
	class IComponent;
	class IMessage {
	public:
		IComponent* src;
		virtual ~IMessage() = 0;
	};
}

#endif
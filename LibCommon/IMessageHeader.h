#ifndef LIBCOMMON_IMESSAGEHEADER_H
#define LIBCOMMON_IMESSAGEHEADER_H

#include "IComponent.h"
namespace LibCommon {
	class IMessageHeader {
	public:
		IComponent* source;
		virtual ~IMessageHeader() = 0;
	};
}

#endif
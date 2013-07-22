#ifndef LIBCOMMON_IMESSAGE_H
#define LIBCOMMON_IMESSAGE_H
#include "stdafx.h"

namespace LibCommon {
	class IMessage {
	public:
		virtual ~IMessage() = 0;
	};
	//body for the virtual destructor, must be outside class
	//for standards complience and in order to compile with g++
	inline IMessage::~IMessage() {}
}

#endif

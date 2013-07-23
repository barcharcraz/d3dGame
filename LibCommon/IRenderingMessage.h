#ifndef LIBCOMMON_RENDERINGMESSAGE_H
#define LIBCOMMON_RENDERINGMESSAGE_H
#include "stdafx.h"
#include "IMessage.h"
namespace LibCommon {
	class IRenderingMessage : public IMessage {
	public:
		virtual ~IRenderingMessage() = 0;
	};
	inline IRenderingMessage::~IRenderingMessage() {}
}
#endif

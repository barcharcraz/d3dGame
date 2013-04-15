#ifndef LIBCOMMON_RENDERINGMESSAGE_H
#define LIBCOMMON_RENDERINGMESSAGE_H
#include "stdafx.h"
#include "IMessage.h"
namespace LibCommon {
	class RenderingMessage : public IMessage {
	public:
		virtual ~RenderingMessage() = 0;
	};
	inline RenderingMessage::~RenderingMessage() {}
}
#endif

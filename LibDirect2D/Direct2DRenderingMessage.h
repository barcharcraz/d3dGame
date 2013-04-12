#pragma once
#include "stdafx.h"
#include <LibCommon\RenderingMessage.h>

namespace LibDirect2D {
	class Direct2DRenderingMessage : public LibCommon::RenderingMessage {
	public:
		Direct2DRenderingMessage(ID2D1DeviceContext &context);
		
		ID2D1DeviceContext &pContext;
	};
}
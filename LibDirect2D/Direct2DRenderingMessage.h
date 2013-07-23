#pragma once
#include "stdafx.h"
#include <LibCommon\IRenderingMessage.h>

namespace LibDirect2D {
	class Direct2DRenderingMessage : public LibCommon::IRenderingMessage {
	public:
		Direct2DRenderingMessage(CComPtr<ID2D1DeviceContext> context);
		
		CComPtr<ID2D1DeviceContext> pContext;
	};
}
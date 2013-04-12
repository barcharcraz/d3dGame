#pragma once
#include "stdafx.h"
#include "Direct2DRenderingMessage.h"
using namespace LibDirect2D;

Direct2DRenderingMessage::Direct2DRenderingMessage(ID2D1DeviceContext &context)
	: pContext(context) {
		src = nullptr;
}
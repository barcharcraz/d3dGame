#include "stdafx.h"
#include "Direct3DRenderingMessage.h"

namespace LibDirect3D {
	Direct3DRenderingMessage::Direct3DRenderingMessage(ID3D11Device1 *device, ID3D11DeviceContext1 *context) 
		: pDevice(device), pContext(context) {
	}
}
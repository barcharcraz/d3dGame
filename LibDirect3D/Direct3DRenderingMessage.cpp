#include "stdafx.h"
#include "Direct3DRenderingMessage.h"
#include "Shaders.h"

namespace LibDirect3D {
	Direct3DRenderingMessage::Direct3DRenderingMessage(ID3D11Device2 *device, ID3D11DeviceContext2 *context, Shaders* shaders) 
		: pDevice(device), pContext(context), pShaders(shaders) {
	}
}
#include "stdafx.h"
#include "Direct3DRenderingMessage.h"

namespace LibDirect3D {
	Direct3DRenderingMessage::Direct3DRenderingMessage(ID3D11Device2 *device, ID3D11DeviceContext2 *context) 
		: pDevice(device), pContext(context) {
	}
}
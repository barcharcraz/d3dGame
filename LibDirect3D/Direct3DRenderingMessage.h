#pragma once
#include "stdafx.h"
#include "Shaders.h"
#include <LibCommon/RenderingMessage.h>
#include <DirectXMath.h>
namespace LibDirect3D {
	class Direct3DRenderingMessage : public LibCommon::RenderingMessage {
	public:
		Direct3DRenderingMessage(ID3D11Device2 *device, ID3D11DeviceContext2 *context, Shaders *shaders);

		Shaders * pShaders;

		//these pointers are not owning /please/ do not delete them
		ID3D11Device2 * pDevice;
		ID3D11DeviceContext2 * pContext;
	
	};
}
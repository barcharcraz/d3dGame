#pragma once
#include "stdafx.h"
#include "Shaders.h"
#include <LibCommon/RenderingMessage.h>
#include <DirectXMath.h>
namespace LibDirect3D {
	class Direct3DRenderingMessage : public LibCommon::RenderingMessage {
	public:
		Direct3DRenderingMessage(ID3D11Device1 *device, ID3D11DeviceContext1 *context);

		Shaders * pShaders;

		//these pointers are not owning /please/ do not delete them
		ID3D11Device1 * pDevice;
		ID3D11DeviceContext1 * pContext;
	
	};
}
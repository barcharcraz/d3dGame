#pragma once
#include "stdafx.h"
#include <LibCommon/RenderingMessage.h>
#include <DirectXMath.h>
namespace LibDirect3D {
	class Direct3DRenderingMessage : public LibCommon::RenderingMessage {
	public:
		Direct3DRenderingMessage(ID3D11Device1 *device, ID3D11DeviceContext1 *context);

		std::vector<ID3D11PixelShader> PSvec;
		ID3D11PixelShader * defaultPS; //this points to something in PSvec

		std::vector<ID3D11VertexShader> VSvec;
		ID3D11VertexShader * defaultVS; //this points to something in VSvec

		//these pointers are not owning /please/ do not delete them
		ID3D11Device1 * pDevice;
		ID3D11DeviceContext1 * pContext;
	
	};
}
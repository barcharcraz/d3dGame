#pragma once
#include "stdafx.h"
#include <LibImage/image.h>
namespace LibDirect3D {
	class Direct3DTexture {
	public:
		Direct3DTexture(const Image::ImageData& data);
		void SetRenderState(CComPtr<ID3D11Device> pDev, CComPtr<ID3D11DeviceContext> pCtx);
		ID3D11Texture2D* Texture(ID3D11Device* pDev);
		ID3D11ShaderResourceView* SRV(ID3D11Device* pDev);
		ID3D11SamplerState* SamplerState(ID3D11Device* pDev);
	private:
		void initTexture(CComPtr<ID3D11Device> pDev);
		void initView(CComPtr<ID3D11Device> pDev);
		void initSampleState(CComPtr<ID3D11Device> pDev);
		CComPtr<ID3D11Texture2D> _texture;
		CComPtr<ID3D11ShaderResourceView> _textureView;
		CComPtr<ID3D11SamplerState> _sampleState;
		Image::ImageData _data;
	};
}
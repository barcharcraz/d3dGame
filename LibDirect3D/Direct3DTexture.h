#pragma once
#include "stdafx.h"
#include <LibImage/image.h>
#include <LibComponents/Texture.h>
#include <RenderingUtils/TextureFunctions.h>
#include <vector>
namespace LibDirect3D {
    
	class Direct3DTexture {
	public:
		Direct3DTexture(const Components::Texture& tex);
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
        const Components::Texture* m_tex;
	};

    //freestanding helper functions
    UINT texMiscFlags(utils::tex::texture_type_e textype);
    std::vector<D3D11_SUBRESOURCE_DATA> texGenSubresources(
        const Image::ImageData* data, utils::tex::texture_type_e type);
    std::vector<D3D11_SUBRESOURCE_DATA> texCubemapGenSubresources(
        const Image::ImageData* data);
    D3D11_SUBRESOURCE_DATA tex2DGenSubresource(const Image::ImageData* data);
}
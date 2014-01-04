#include "stdafx.h"
#include "Direct3DTexture.h"
#include <LibImage/image.h>
#include <LibImage/conversions.h>
#include <RenderingUtils/TextureFunctions.h>
#include <Utils/exceptions.h>
#include <vector>
namespace LibDirect3D {
    Direct3DTexture::Direct3DTexture(const Components::Texture& tex)
        : m_tex(&tex)
    {

    }
    void Direct3DTexture::SetRenderState(CComPtr<ID3D11Device> pDev, CComPtr<ID3D11DeviceContext> pCtx) {
        if (_texture == nullptr) {
            initTexture(pDev);
        }
        if (_textureView == nullptr) {
            initView(pDev);
        }
        if (_sampleState == nullptr) {
            initSampleState(pDev);
        }
        pCtx->PSSetShaderResources(0, 1, &_textureView.p);
        pCtx->PSSetSamplers(0, 1, &_sampleState.p);
    }
    ID3D11Texture2D* Direct3DTexture::Texture(ID3D11Device* pDev) {
        if (nullptr == _texture) {
            initTexture(pDev);
        }
        return _texture;
    }
    ID3D11ShaderResourceView* Direct3DTexture::SRV(ID3D11Device* pDev) {
        if (nullptr == _textureView) {
            initView(pDev);
        }
        return _textureView;
    }
    ID3D11SamplerState* Direct3DTexture::SamplerState(ID3D11Device* pDev) {
        if (nullptr == _sampleState) {
            initSampleState(pDev);
        }
        return _sampleState;
    }
    //-------PRIVATE-----------
    void Direct3DTexture::initTexture(CComPtr<ID3D11Device> pDev) {
        using Image::ImageData;
        ImageData dat = Image::Conversions::ConvertImage(m_tex->data(), Image::Formats::R8G8B8A8_UNORM);
        D3D11_TEXTURE2D_DESC desc;
        desc.Width = dat.width;
        desc.Height = dat.height;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.MipLevels = 1;
        desc.ArraySize = utils::tex::numTexArrays(m_tex->type);
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE_IMMUTABLE;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = texMiscFlags(m_tex->type);
        auto subdescs = texGenSubresources(&dat, m_tex->type);
        
        HRESULT hr = S_OK;
        hr = pDev->CreateTexture2D(&desc, subdescs.data(), &_texture);
        if (FAILED(hr)) {
            throw std::runtime_error("could not create texture resouce");
        }
    }
    void Direct3DTexture::initView(CComPtr<ID3D11Device> pDev) {
        HRESULT hr = S_OK;
        if (nullptr == _texture) {
            initTexture(pDev);
        }
        hr = pDev->CreateShaderResourceView(_texture, nullptr, &_textureView);
        if (FAILED(hr)) {
            throw std::system_error(hr, std::system_category());
        }
    }
    void Direct3DTexture::initSampleState(CComPtr<ID3D11Device> pDev) {
        D3D11_SAMPLER_DESC desc;
        desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        desc.MipLODBias = 0.0f;
        desc.MaxAnisotropy = 1;
        desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        desc.BorderColor[0] = 0;
        desc.BorderColor[1] = 0;
        desc.BorderColor[2] = 0;
        desc.BorderColor[3] = 0;
        desc.MinLOD = 0;
        desc.MaxLOD = D3D11_FLOAT32_MAX;

        HRESULT hr = S_OK;
        hr = pDev->CreateSamplerState(&desc, &_sampleState);
        if (FAILED(hr)) {
            throw std::system_error(hr, std::system_category());
        }

    }
    //freestanding helper functions
    UINT texMiscFlags(utils::tex::texture_type_e textype) {
        switch (textype) {
        case utils::tex::TEXTURE2D_CUBEMAP:
            return D3D11_RESOURCE_MISC_TEXTURECUBE;
        default:
            return 0;
        }
    }
    std::vector<D3D11_SUBRESOURCE_DATA> texGenSubresources(
        const Image::ImageData* tex, utils::tex::texture_type_e type) 
    {
        using namespace utils::tex;
        std::vector<D3D11_SUBRESOURCE_DATA> rv;
        switch (type) {
        case TEXTURE2D:
            rv.push_back(tex2DGenSubresource(tex));
            break;
        case TEXTURE2D_CUBEMAP:
            rv = texCubemapGenSubresources(tex);
            break;
        default:
            throw utils::invalid_enum_error("invalid texture type");
            break;
        }
        return rv;
    }
    std::vector<D3D11_SUBRESOURCE_DATA> texCubemapGenSubresources(
        const Image::ImageData* data) 
    {
        using namespace utils::tex;
        std::vector<D3D11_SUBRESOURCE_DATA> rv;
        for (int i = PLUS_X; i < MAX_SIDES; ++i) {
            D3D11_SUBRESOURCE_DATA next;
            auto curFace = static_cast<cubemap_face_e>(i);
            memset(&next, 0, sizeof(D3D11_SUBRESOURCE_DATA));
            next.SysMemPitch = 4 * data->width;
            next.SysMemSlicePitch = static_cast<UINT>(data->data.size() * 4);
            int offset = cubemapSquareOffset(curFace, data->width);
            next.pSysMem = &data->data[offset * 4];
            rv.push_back(next);
        }
        return rv;
    }
    D3D11_SUBRESOURCE_DATA tex2DGenSubresource(const Image::ImageData* data) {
        D3D11_SUBRESOURCE_DATA dat;
        dat.pSysMem = &data->data[0];
        dat.SysMemPitch = 4 * data->width;
        dat.SysMemSlicePitch = static_cast<UINT>(data->data.size() * 4);
        return dat;
    }
}
#include "stdafx.h"
#include "Direct3DRenderer.h"
#include <stdexcept>
#include <cassert>
using namespace LibDirect3D;
Direct3DRenderer::Direct3DRenderer() {
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    init(nullptr, D3D_DRIVER_TYPE_REFERENCE, 0, creationFlags, defaultFeatureLevels, defaultNumFeatureLevels, D3D11_SDK_VERSION, nullptr);
}
Direct3DRenderer::Direct3DRenderer(HWND target) {
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    init(nullptr, D3D_DRIVER_TYPE_REFERENCE, 0, creationFlags, defaultFeatureLevels, defaultNumFeatureLevels, D3D11_SDK_VERSION, nullptr);
    bindToHwnd(target);
}
Direct3DRenderer::Direct3DRenderer(windowing::IDXWindow* win)
: Direct3DRenderer()
{
    bindToHwnd(reinterpret_cast<HWND>(win->Handle()));
    Attach(win);
}
Direct3DRenderer::~Direct3DRenderer() {
    Detach();
}
void Direct3DRenderer::init(IDXGIAdapter* pAdapter,
            D3D_DRIVER_TYPE type,
            HMODULE software,
            UINT flags,
            const D3D_FEATURE_LEVEL* plevels,
            UINT numLevels,
            UINT sdkVersion,
            D3D_FEATURE_LEVEL* outLevel) {

                CComPtr<ID3D11Device> pDevice;
                CComPtr<ID3D11DeviceContext> pContext;
                HRESULT hr =  D3D11CreateDevice(pAdapter, type, software, flags, plevels, numLevels, sdkVersion, &pDevice, outLevel, &pContext);
                if(FAILED(hr)) {
                    throw hr;
                }

                //and assign contexts
                hr = pDevice.QueryInterface(&pDev);
                if (FAILED(hr)) {
                    throw hr;
                }

                hr = pContext.QueryInterface(&pCtx);
                if (FAILED(hr)) {
                    throw hr;
                }

                //set the dxgi device
                hr = pDev.QueryInterface(&m_pDXGIDevice);
                if(FAILED(hr)) {
                    throw hr;
                }
                m_pDXGIFactory = LibDXGI::GetFactory(m_pDXGIDevice);
}

void Direct3DRenderer::bindToHwnd(HWND target) {
    DXGI_SWAP_CHAIN_DESC1 defChain = LibDXGI::GetDefaultSwapChain();
    CComPtr<IDXGISwapChain1> pSwapChain;
    HRESULT hr = m_pDXGIFactory->CreateSwapChainForHwnd(m_pDXGIDevice, target, &defChain, nullptr, nullptr, &pSwapChain);
    //at this point we have not actually changed the state of the object
    if (FAILED(hr)) {
        throw hr;
    }
    //and now we change the state of the object
    hr = pSwapChain.QueryInterface(&m_pSwapChain);
    if (FAILED(hr)) {
        throw hr;
    }
    createRenderTarget();
    setViewports();
    createDepthStencil();
    
}
void Direct3DRenderer::Attach(windowing::IDXWindow* target) {
    if (m_win != nullptr) {
        Detach();
    }
    m_win = target;
    target->SetPresentOverride([this](){this->Present(); });
    target->SetClearOverride([this](){this->Clear(); });
}
void Direct3DRenderer::Detach() {
    m_win->SetPresentOverride(nullptr);
    m_win->SetClearOverride(nullptr);
    m_win = nullptr;
}
void Direct3DRenderer::createRenderTarget() {
    HRESULT hr = S_OK;
    CComPtr<ID3D11Texture2D> buffer;
    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**) &buffer);
    if (FAILED(hr)) {
        throw hr;
    }
    D3D11_RENDER_TARGET_VIEW_DESC desc;
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MipSlice = 0;

    hr = pDev->CreateRenderTargetView(buffer, &desc, &m_pRenderTarget);
    if (FAILED(hr)) {
        throw hr;
    }
}
void Direct3DRenderer::createDepthStencil() {
    HRESULT hr = S_OK;
    //we need the swap chain description
    //so that we can tell what the size
    //of our target is
    DXGI_SWAP_CHAIN_DESC swapDesc;
    hr = m_pSwapChain->GetDesc(&swapDesc);
    if (FAILED(hr)) {
        throw hr;
    }
    
    D3D11_TEXTURE2D_DESC desc;
    desc.Width = swapDesc.BufferDesc.Width;
    desc.Height = swapDesc.BufferDesc.Height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    hr = pDev->CreateTexture2D(&desc, nullptr, &_pDepthStencil);
    if (FAILED(hr)) {
        throw hr;
    }

    D3D11_DEPTH_STENCIL_DESC dsDesc;
    dsDesc.DepthEnable = true;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
    dsDesc.StencilEnable = true;
    dsDesc.StencilReadMask = 0xFF;
    dsDesc.StencilWriteMask = 0xFF;

    dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    hr = pDev->CreateDepthStencilState(&dsDesc, &_pdsState);
    if (FAILED(hr)) {
        throw hr;
    }
    

    hr = pDev->CreateDepthStencilView(_pDepthStencil, nullptr, &_pdsView);
    if (FAILED(hr)) {
        throw hr;
    }
    pCtx->OMSetDepthStencilState(_pdsState, 1);
}
void Direct3DRenderer::setViewports() {
    HRESULT hr = S_OK;
    DXGI_SWAP_CHAIN_DESC swd;
    hr = m_pSwapChain->GetDesc(&swd);
    if (FAILED(hr)) {
        throw hr;
    }
    D3D11_VIEWPORT port;
    port.TopLeftX = 0;
    port.TopLeftY = 0;
    port.MinDepth = 0;
    port.MaxDepth = 1;
    port.Height = static_cast<float>(swd.BufferDesc.Height);
    port.Width = static_cast<float>(swd.BufferDesc.Width);
    pCtx->RSSetViewports(1, &port);
}

void Direct3DRenderer::Present() {
    
    DXGI_PRESENT_PARAMETERS params;
    params.DirtyRectsCount = 0;
    params.pDirtyRects = nullptr;
    params.pScrollRect = nullptr;
    params.pScrollOffset = nullptr;
    
    m_pSwapChain->Present1(1, 0, &params);
    
    
    
}
void Direct3DRenderer::Clear() {
    float color [] = { 0.0f, 0.0f, 0.0f, 0.0f };
    pCtx->OMSetRenderTargets(1, &m_pRenderTarget.p, _pdsView);
    pCtx->ClearRenderTargetView(m_pRenderTarget, color);
    pCtx->ClearDepthStencilView(_pdsView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}
void Direct3DRenderer::DisableAlphaBlending() {
    pCtx->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}
void Direct3DRenderer::EnableAlphaBlending() {
    HRESULT hr = S_OK;
    if (nullptr == _bsOn) {
        D3D11_BLEND_DESC desc;
        D3D11_RENDER_TARGET_BLEND_DESC rtBlend;
        rtBlend.BlendEnable = true;
        rtBlend.SrcBlend = D3D11_BLEND_SRC_ALPHA;
        rtBlend.BlendOpAlpha = D3D11_BLEND_OP_ADD;
        rtBlend.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        rtBlend.DestBlendAlpha = D3D11_BLEND_ZERO;
        rtBlend.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        rtBlend.SrcBlendAlpha = D3D11_BLEND_ZERO;
        rtBlend.BlendOp = D3D11_BLEND_OP_ADD;
        desc.AlphaToCoverageEnable = false;
        desc.IndependentBlendEnable = false;
        for (unsigned int i = 0; i < 8; ++i) {
            desc.RenderTarget[i] = rtBlend;
        }
        hr = pDev->CreateBlendState(&desc, &_bsOn);
        if (FAILED(hr)) {
            throw std::system_error(hr, std::system_category());
        }

    }
    pCtx->OMSetBlendState(_bsOn, nullptr, 0xffffffff);
}
CComPtr<IDXGISwapChain2> Direct3DRenderer::GetSwapChain() {
    return m_pSwapChain;
}
CComPtr<IDXGIDevice3> Direct3DRenderer::GetDXGIDevice() {
    return m_pDXGIDevice;
}
//creation utilities
CComPtr<ID3D11Buffer> Direct3DRenderer::CreateIndexBuffer(const Components::Model& model) const {
    HRESULT hr = S_OK;
    CComPtr<ID3D11Buffer> indexBuffer;
    D3D11_BUFFER_DESC indexDesc;
    indexDesc.Usage = D3D11_USAGE_DEFAULT;
    indexDesc.ByteWidth = static_cast<UINT>(sizeof(unsigned int) * model.indices.size());
    indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexDesc.CPUAccessFlags = 0;
    indexDesc.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA indexData;
    indexData.pSysMem = model.indices.data();
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;
    hr = pDev->CreateBuffer(&indexDesc, &indexData, &indexBuffer);
    if (FAILED(hr)) {
        throw hr;
    }
    return indexBuffer;
}
CComPtr<ID3D11Buffer> Direct3DRenderer::CreateVertexBuffer(const Components::Model& model) const {
    HRESULT hr = S_OK;
    CComPtr<ID3D11Buffer> vertexBuffer;
    D3D11_BUFFER_DESC vertexDesc;
    vertexDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexDesc.ByteWidth = static_cast<UINT>(sizeof(LibCommon::Vertex) * model.verts.size());
    vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexDesc.CPUAccessFlags = 0;
    vertexDesc.MiscFlags = 0;
    vertexDesc.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = model.verts.data();
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;
    hr = pDev->CreateBuffer(&vertexDesc, &vertexData, &vertexBuffer);
    if (FAILED(hr)) {
        throw hr;
    }
    return vertexBuffer;
}
CComPtr<ID3D11Buffer> Direct3DRenderer::CreateConstantBuffer(size_t size) const {
    HRESULT hr = S_OK;
    CComPtr<ID3D11Buffer> retval;
    D3D11_BUFFER_DESC desc;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.ByteWidth = static_cast<UINT>(size);
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;
    hr = pDev->CreateBuffer(&desc, nullptr, &retval);
    if (FAILED(hr)) {
        throw std::system_error(hr, std::system_category());
    }
    return retval;
    
}
CComPtr<ID3D11Buffer> Direct3DRenderer::CreateConstantBuffer(const void* data, size_t size) const {
    HRESULT hr = S_OK;
    CComPtr<ID3D11Buffer> retval;
    D3D11_BUFFER_DESC desc;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.ByteWidth = static_cast<UINT>(size);
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA dat;
    dat.pSysMem = data;
    dat.SysMemPitch = 0;
    dat.SysMemSlicePitch = 0;

    hr = pDev->CreateBuffer(&desc, &dat, &retval);
    if (FAILED(hr)) {
        throw std::system_error(hr, std::system_category());
    }
    return retval;
}

CComPtr<ID3D11Buffer> Direct3DRenderer::GetTransforms(const LibCommon::Transforms& transforms) const {
    HRESULT hr = S_OK;
    if (_transformBuffer == nullptr) {
        _transformBuffer = CreateConstantBuffer(sizeof(transforms));
    }
    D3D11_MAPPED_SUBRESOURCE map;
    map.pData = 0;
    map.DepthPitch = 0;
    map.RowPitch = 0;
    hr = pCtx->Map(_transformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
    if (FAILED(hr)) {
        throw std::system_error(hr, std::system_category());
    }
    memcpy(map.pData, &transforms, sizeof(transforms));
    pCtx->Unmap(_transformBuffer, 0);
    return _transformBuffer;
}
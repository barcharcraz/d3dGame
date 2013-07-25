#include "stdafx.h"
#include "Direct3DRenderer.h"
using namespace LibDirect3D;
Direct3DRenderer::Direct3DRenderer() : m_pShaders(std::make_unique<Shaders>()) {
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	init(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags, defaultFeatureLevels, defaultNumFeatureLevels, D3D11_SDK_VERSION, nullptr);
}
Direct3DRenderer::Direct3DRenderer(HWND target) : m_pShaders(std::make_unique<Shaders>()) {
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	init(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags, defaultFeatureLevels, defaultNumFeatureLevels, D3D11_SDK_VERSION, nullptr);
	bindToHwnd(target);
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
				hr = pDevice.QueryInterface(&m_pDevice);
				if (FAILED(hr)) {
					throw hr;
				}

				hr = pContext.QueryInterface(&m_pContext);
				if (FAILED(hr)) {
					throw hr;
				}

				//set the dxgi device
				hr = m_pDevice.QueryInterface(&m_pDXGIDevice);
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
void Direct3DRenderer::createRenderTarget() {
	HRESULT hr = S_OK;
	CComPtr<ID3D11Texture2D> buffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**) &buffer);
	if (FAILED(hr)) {
		throw hr;
	}
	
	hr = m_pDevice->CreateRenderTargetView(buffer, NULL, &m_pRenderTarget);
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
	hr = m_pDevice->CreateTexture2D(&desc, nullptr, &_pDepthStencil);
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

	hr = m_pDevice->CreateDepthStencilState(&dsDesc, &_pdsState);
	if (FAILED(hr)) {
		throw hr;
	}
	

	hr = m_pDevice->CreateDepthStencilView(_pDepthStencil, nullptr, &_pdsView);
	if (FAILED(hr)) {
		throw hr;
	}
	m_pContext->OMSetDepthStencilState(_pdsState, 1);
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
	m_pContext->RSSetViewports(1, &port);
}
LibCommon::IMessage * Direct3DRenderer::getRenderingMessage() {
	if(lazyMessage == nullptr) {
		lazyMessage.reset(new Direct3DRenderingMessage(m_pDevice, m_pContext, m_pShaders.get()));
	}
	//return a non-owning raw pointer
	return lazyMessage.get();
}

void Direct3DRenderer::addPixelShader(const std::string &name, const BYTE shaderBlob[], size_t shaderSize, const std::vector<D3D11_INPUT_ELEMENT_DESC> &desc) {
	m_pShaders->addPS(m_pDevice, name, shaderBlob, shaderSize, desc);
}
void Direct3DRenderer::addVertexShader(const std::string &name, const BYTE shaderBlob [], size_t shaderSize, const std::vector<D3D11_INPUT_ELEMENT_DESC> &desc) {
	m_pShaders->addVS(m_pDevice, name, shaderBlob, shaderSize, desc);
}
void Direct3DRenderer::addPixelShader(const std::string& filename, const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc) {
	m_pShaders->addVS(m_pDevice, filename, desc);
}
void Direct3DRenderer::addVertexShader(const std::string& filename, const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc) {
	m_pShaders->addPS(m_pDevice, filename, desc);
}
void Direct3DRenderer::addPixelShader(const std::string& filename) {
	m_pShaders->addPS(m_pDevice, filename, defaultLayout);
}
void Direct3DRenderer::addVertexShader(const std::string& filename) {
	m_pShaders->addVS(m_pDevice, filename, defaultLayout);
}

void Direct3DRenderer::Present() {
	
	DXGI_PRESENT_PARAMETERS params;
	params.DirtyRectsCount = 0;
	params.pDirtyRects = nullptr;
	params.pScrollRect = nullptr;
	params.pScrollOffset = nullptr;
	
	m_pSwapChain->Present1(1, 0, &params);
	
	float color [] = { 1.0f, 0.0f, 0.0f, 0.0f };
	m_pContext->OMSetRenderTargets(1, &m_pRenderTarget.p, _pdsView);
	m_pContext->ClearRenderTargetView(m_pRenderTarget, color);
	m_pContext->ClearDepthStencilView(_pdsView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	
}
void Direct3DRenderer::Clear() {
	
}
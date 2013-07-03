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
	m_pSwapChain->Present1(0, 0, &params);
	DXGI_RGBA clearColor;
	clearColor.r = 1.0f;
	clearColor.g = 0;
	clearColor.b = 0;
	clearColor.a = 1.0f;
	//m_pSwapChain->SetBackgroundColor(&clearColor);
}
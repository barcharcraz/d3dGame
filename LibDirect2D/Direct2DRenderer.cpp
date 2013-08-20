#include "stdafx.h"
#include <d3d11_1.h>
#include "Direct2DRenderer.h"
#include <stdexcept>
using namespace LibDirect2D;

Direct2DRenderer::Direct2DRenderer(IDXGIDevice* pDev, IDXGISwapChain1* pSwap) {
	init(pDev, pSwap);
}
void Direct2DRenderer::Clear() {
	pContext->Clear(D2D1::ColorF{ D2D1::ColorF::Black });
}
void Direct2DRenderer::init(IDXGIDevice* pDev, IDXGISwapChain1* pSwap) {
	HRESULT hr = S_OK;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
	if (FAILED(hr)) {
		throw std::system_error(hr, std::system_category());
	}
	hr = pFactory->CreateDevice(pDev, &pDevice);
	if (FAILED(hr)) {
		throw std::system_error(hr, std::system_category());
	}
	hr = pDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &pContext);
	if (FAILED(hr)) {
		throw std::system_error(hr, std::system_category());
	}

	m_pSwapChain = pSwap;
	hr = m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pSurface));
	if (FAILED(hr)) {
		throw std::system_error(hr, std::system_category());
	}
	float dpiX;
	float dpiY;
	pFactory->GetDesktopDpi(&dpiX, &dpiY);
	D2D1_BITMAP_PROPERTIES1 props;
	props.dpiX = dpiX;
	props.dpiY = dpiY;
	props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	props.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	props.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	props.colorContext = nullptr;
	hr = pContext->CreateBitmapFromDxgiSurface(pSurface, &props, &pBitmap);
	if (FAILED(hr)) {
		throw std::system_error(hr, std::system_category());
	}
	
	
}
void Direct2DRenderer::SetRenderTarget() const {
	pContext->SetTarget(pBitmap);
}
D2D1_MATRIX_3X2_F Direct2DRenderer::GetProjection() const {
	DXGI_SWAP_CHAIN_DESC1 desc;
	HRESULT hr = S_OK;
	hr = m_pSwapChain->GetDesc1(&desc);
	if (FAILED(hr)) {
		throw std::system_error(hr, std::system_category());
	}
	auto proj = D2D1::Matrix3x2F::Scale(desc.Width / 2, desc.Height / 2);
	proj = proj * D2D1::Matrix3x2F::Translation(desc.Width / 2, desc.Height / 2);
	return proj;
}

CComPtr<ID2D1DeviceContext> Direct2DRenderer::getContext() const {
	return pContext;
}
Direct2DRenderer::~Direct2DRenderer() {
	
}
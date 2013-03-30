#include "Direct2DRenderer.h"
using namespace LibDirect2D;

Direct2DRenderer::Direct2DRenderer(IDXGIDevice* pdxgidevice, HWND target) {
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
	if(FAILED(hr)) {
		throw hr;
	}
	hr = pFactory->CreateDevice(pdxgidevice, &pDevice);
	if(FAILED(hr)) {
		throw hr;
	}
	hr = pDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &pContext);
	if(FAILED(hr)) {
		throw hr;
	}
	m_pSwapChain = LibDXGI::CreateSwapChain(pdxgidevice, target);
	
}
CComPtr<ID2D1Bitmap1> Direct2DRenderer::getBackBufferBitmap() {
	return getBackBufferBitmap(pContext, m_pSwapChain);
}
CComPtr<ID2D1Bitmap1> Direct2DRenderer::getBackBufferBitmap(ID2D1DeviceContext* pContext, IDXGISwapChain1* pSwapChain) {
	
	D2D1_BITMAP_PROPERTIES1 prop = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE));
	CComPtr<IDXGISurface> backBuffer;
	HRESULT hr = pSwapChain->GetBuffer(0,IID_PPV_ARGS(&backBuffer));
	if(FAILED(hr)) {
		throw hr;
	}
	CComPtr<ID2D1Bitmap1> retval;
	pContext->CreateBitmapFromDxgiSurface(backBuffer, prop, &retval);
	return retval;

}
Direct2DRenderingMessage Direct2DRenderer::getRenderingMessage() {
	//lots of copying here but I am not convinced the object is big enough to
	//justify passing it around by reference
	Direct2DRenderingMessage retval = Direct2DRenderingMessage(pContext);
	return retval;
}




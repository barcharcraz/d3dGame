#pragma once
#include "stdafx.h"
#include <d3d11_1.h>
#include <atlbase.h>
#include <LibCommon\IRenderer.h>
namespace LibDirect2D {
class Direct2DRenderer : public LibCommon::IRenderer {
public:
	Direct2DRenderer(HWND target);
	Direct2DRenderer(IDXGIDevice* pdxgidevice, HWND target);
	void Present();

	CComPtr<ID2D1DeviceContext> getContext() const;
	~Direct2DRenderer();
private:
	void init(IDXGIDevice* pDev, IDXGISwapChain1* pSwap);
	void init(IDXGIDevice* pdxgidevice, HWND target);

	CComPtr<ID3D11Device> p3Device;
	CComPtr<IDXGIDevice> pDxgiDevice;
	CComPtr<ID3D11DeviceContext> pD3DContext;
	CComPtr<ID2D1Factory1> pFactory;
	CComPtr<ID2D1Device> pDevice;
	CComPtr<ID2D1DeviceContext> pContext;
	CComPtr<IDXGISwapChain1> m_pSwapChain;
	CComPtr<ID2D1Bitmap1> getBackBufferBitmap();
	static CComPtr<ID2D1Bitmap1> getBackBufferBitmap(ID2D1DeviceContext* pContect, IDXGISwapChain1* pSwapChain);
	
	
};
}
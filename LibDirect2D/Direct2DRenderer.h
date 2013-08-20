#pragma once
#include "stdafx.h"
#include <d3d11_1.h>
#include <atlbase.h>
#include <LibCommon\IRenderer.h>
namespace LibDirect2D {
class Direct2DRenderer : public LibCommon::IRenderer {
public:
	Direct2DRenderer(IDXGIDevice* pDev, IDXGISwapChain1* pSwap);
	void Clear();
	D2D1_MATRIX_3X2_F GetProjection() const;
	CComPtr<ID2D1DeviceContext> getContext() const;
	void SetRenderTarget() const;
	~Direct2DRenderer();
private:
	void init(IDXGIDevice* pDev, IDXGISwapChain1* pSwap);

	CComPtr<ID3D11Device> p3Device;
	CComPtr<IDXGIDevice> pDxgiDevice;
	CComPtr<ID3D11DeviceContext> pD3DContext;
	CComPtr<ID2D1Factory1> pFactory;
	CComPtr<ID2D1Device> pDevice;
	CComPtr<ID2D1DeviceContext> pContext;
	CComPtr<ID2D1Bitmap1> pBitmap;
	CComPtr<IDXGISwapChain1> m_pSwapChain;
	CComPtr<IDXGISurface> pSurface;
};
}
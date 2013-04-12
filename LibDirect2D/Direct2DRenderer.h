#pragma once
#include "stdafx.h"
#include "Direct2DRenderingMessage.h"
#include <atlbase.h>
#include <LibCommon\IRenderer.h>
namespace LibDirect2D {
class Direct2DRenderer : public LibCommon::IRenderer {
public:
	Direct2DRenderer(HWND target);
	Direct2DRenderer(IDXGIDevice* pdxgidevice, HWND target);
	LIBDIRECT2D_API virtual const Direct2DRenderingMessage* const getRenderingMessage() override;
	void Present();

	ID2D1DeviceContext& getContext();
private:
	CComPtr<ID2D1Factory1> pFactory;
	CComPtr<ID2D1Device> pDevice;
	CComPtr<ID2D1DeviceContext> pContext;
	CComPtr<IDXGISwapChain1> m_pSwapChain;
	CComPtr<ID2D1Bitmap1> getBackBufferBitmap();
	static CComPtr<ID2D1Bitmap1> getBackBufferBitmap(ID2D1DeviceContext* pContect, IDXGISwapChain1* pSwapChain);
	
	
};
}
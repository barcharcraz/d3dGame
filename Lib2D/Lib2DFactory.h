#pragma once
#include<atlbase.h>
#include<memory>
#include "Lib2DDevice.h"
#include<d2d1_1.h>
#include<d3d11_1.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")
///-------------------------------------------------------------------------------------------------
/// <summary>	Factory for Lib2D resources. </summary>
///
/// <remarks>	Charlie, 10/5/2012. </remarks>
///-------------------------------------------------------------------------------------------------

class Lib2DFactory {
public:
	Lib2DFactory(HWND target);
	Lib2DFactory(ID3D11Device *device, HWND target);
	~Lib2DFactory();
	std::shared_ptr<Lib2DDevice> createLib2DDevice();
	CComPtr<IDXGISurface> getBackBuffer();
	CComPtr<IDXGISwapChain1> getSwapChain();
private:
	CComPtr<ID2D1Factory1> m_factory;
	CComPtr<IDXGIDevice> m_device;
	CComPtr<IDXGISwapChain1> m_swapChain;
	CComPtr<ID3D11Device> createDevice();
	CComPtr<IDXGISwapChain1> createSwapChain(HWND target);
	DXGI_SWAP_CHAIN_DESC1 getDefSwapChain();
};


#pragma once
#include<comip.h>
#include<d2d1_1.h>
#include<d3d11_1.h>
///-------------------------------------------------------------------------------------------------
/// <summary>	Factory for Lib2D resources. </summary>
///
/// <remarks>	Charlie, 10/5/2012. </remarks>
///-------------------------------------------------------------------------------------------------

class Lib2DFactory {
public:
	Lib2DFactory();
	Lib2DFactory(ID3D11Device *device);
	~Lib2DFactory();
private:
	_com_ptr_t<ID2D1Factory1> m_factory;
	_com_ptr_t<IDXGIDevice> m_device;
	_com_ptr_t<IDXGISwapChain1> m_swapChain;
	_com_ptr_t<ID3D11Device> createDevice();
	_com_ptr_t<IDXGISwapChain1> createSwapChain(HWND target);
	DXGI_SWAP_CHAIN_DESC1 getDefSwapChain();
};


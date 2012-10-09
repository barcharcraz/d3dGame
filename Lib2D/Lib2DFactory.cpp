#include "Lib2DFactory.h"

Lib2DFactory::Lib2DFactory() {
	D2D1_FACTORY_OPTIONS options;
	options.debugLevel = D2D1_DEBUG_LEVEL_WARNING;
	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), &options, &m_factory);
	if(FAILED(hr)) {
		throw hr;
	}
	m_device = createDevice().QueryInterface(__uuidof(IDXGIDevice), &m_device);
}
Lib2DFactory::Lib2DFactory(ID3D11Device *device) {
	D2D1_FACTORY_OPTIONS options;
	options.debugLevel = D2D1_DEBUG_LEVEL_WARNING;
	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), &options, &m_factory);
	if(FAILED(hr)) {
		throw hr;
	}
	m_device = device;
	
}

_com_ptr_t<ID3D11Device> Lib2DFactory::createDevice()
{
	_com_ptr_t<ID3D11Device> device;
	_com_ptr_t<ID3D11DeviceContext> context;
	UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	HRESULT hr;
	hr = D3D11CreateDevice(nullptr, 
		D3D_DRIVER_TYPE_HARDWARE, 
		0, 
		flags, 
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&device,
		NULL,
		&context);
	
	return device;
}

_com_ptr_t<IDXGISwapChain1> Lib2DFactory::createSwapChain(HWND target)
{
	_com_ptr_t<IDXGISwapChain1> retval;
	HRESULT hr;
	_com_ptr_t<IDXGIAdapter> dxgiAdapter;
	hr = m_device->GetAdapter(&dxgiAdapter);
	if(FAILED(hr)) {
		throw hr;
	}

	_com_ptr_t<IDXGIFactory2> dxgiFactory;
	hr = dxgiAdapter->GetParent(__uuidof(dxgiFactory), &dxgiFactory);
	if(FAILED(hr)) {
		throw hr;
	}
	dxgiFactory->CreateSwapChainForHwnd(m_device, target, getDefSwapChain(), NULL, NULL, &retval);
	return retval;

}

DXGI_SWAP_CHAIN_DESC1 Lib2DFactory::getDefSwapChain()
{
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {0};
	swapChainDesc.Width = 0;                                     // use automatic sizing
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;           // this is the most common swapchain format
	swapChainDesc.Stereo = false; 
	swapChainDesc.SampleDesc.Count = 1;                          // don't use multi-sampling
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;                               // use double buffering to enable flip
	swapChainDesc.Scaling = DXGI_SCALING_NONE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // all Metro style apps must use this SwapEffect
	swapChainDesc.Flags = 0;

	return swapChainDesc;
}

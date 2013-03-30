// LibDXGI.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "LibDXGI.h"


DXGI_SWAP_CHAIN_DESC1 LibDXGI::GetDefaultSwapChain() {
	DXGI_SWAP_CHAIN_DESC1 retval;
	retval.Width = 0;
	retval.Height = 0;
	retval.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	retval.Stereo = false;
	retval.SampleDesc.Count = 1;
	retval.SampleDesc.Quality = 0;
	retval.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	retval.BufferCount = 2;
	retval.Scaling = DXGI_SCALING_NONE;
	retval.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	retval.Flags = 0;
	return retval;
}
CComPtr<IDXGIFactory2> LibDXGI::GetFactory(IDXGIDevice* pDevice) {
	CComPtr<IDXGIAdapter> pAdapter; //temp adapter
	HRESULT hr = pDevice->GetAdapter(&pAdapter);
	if(FAILED(hr)) {
		throw hr;
	}
	CComPtr<IDXGIFactory2> pFactory; //again a temp pointer to a factory
	hr = pAdapter->GetParent(IID_PPV_ARGS(&pFactory)); //and get the factory
	if(FAILED(hr)) {
		throw hr;
	}
	return pFactory;
}
CComPtr<IDXGISwapChain1> LibDXGI::CreateSwapChain(IDXGIDevice* pDevice, HWND target) {
	CComPtr<IDXGIFactory2> pFactory = GetFactory(pDevice);
	CComPtr<IDXGISwapChain1> retval;
	HRESULT hr = pFactory->CreateSwapChainForHwnd(pDevice, target, &GetDefaultSwapChain(), nullptr, nullptr, &retval);
	if(FAILED(hr)) {
		throw hr;
	}
	return retval;
}

#include "stdafx.h"
#include "Device.h"


Device::Device(HWND target)
{
	ZeroMemory( &swapDesc, sizeof(swapDesc) );
	swapDesc.BufferCount = 1;
	swapDesc.BufferDesc.Width = 640;
	swapDesc.BufferDesc.Height = 480;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Numerator = 1;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = target;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.Windowed = TRUE;

	featureLevels.push_back(D3D_FEATURE_LEVEL_11_1);
	featureLevels.push_back(D3D_FEATURE_LEVEL_11_0);
	featureLevels.push_back(D3D_FEATURE_LEVEL_10_1);
	featureLevels.push_back(D3D_FEATURE_LEVEL_10_0);
	featureLevels.push_back(D3D_FEATURE_LEVEL_9_3);
}

HRESULT Device::createDeviceAndSwapChain()
{
	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE, 
		NULL, 
		0,
		featureLevels.data(),
		featureLevels.size(),
		D3D11_SDK_VERSION,
		&swapDesc,
		&swapChain,
		&d3dDevice,
		NULL,
		&d3dDeviceContext);
}

HRESULT Device::createRenderTargetView()
{
	ID3D11Texture2D* pBackBuffer;
	HRESULT hr;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if(FAILED(hr))
	{
		return hr;
	}
	hr = d3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
	if(FAILED(hr))
	{
		return hr;
	}
}
Device::~Device(void)
{
}

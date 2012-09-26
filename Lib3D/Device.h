#pragma once
#pragma comment(lib,"d3d11.lib")
#include <d3d11.h>
#include <vector>
#include "MacroUtils.h"
class LIB3D_API Device
{
public:
	DXGI_SWAP_CHAIN_DESC swapDesc;
	std::vector<D3D_FEATURE_LEVEL> featureLevels;
	IDXGISwapChain* swapChain;
	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* d3dDeviceContext;
	ID3D11RenderTargetView* pRenderTargetView;
	
	
	Device(HWND target);
	~Device(void);
private:
	HRESULT createDeviceAndSwapChain();
	HRESULT createRenderTargetView();
	void setViewports();

	HWND _hwndTarget;
};


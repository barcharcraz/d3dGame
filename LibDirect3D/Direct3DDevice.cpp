#include "Direct3DDevice.h"

namespace LibDirect3D {
	Direct3DDevice::Direct3DDevice(IDXGIAdapter* pAdapter,
		D3D_DRIVER_TYPE type,
		HMODULE software,
		UINT flags,
		const D3D_FEATURE_LEVEL* pLevels,
		UINT numLevels,
		UINT sdkVersion) 
	{
		HRESULT hr = S_OK;
		hr = D3D11CreateDevice(pAdapter, type, software, flags, pLevels, numLevels, sdkVersion, &pDev, &activeLevel, &pCtx);
	}
}
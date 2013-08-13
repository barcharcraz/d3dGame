#pragma once

#include "stdafx.h"

namespace LibDirect3D {
	class Direct3DDevice {
	public:
		Direct3DDevice(IDXGIAdapter* pAdapter,
			D3D_DRIVER_TYPE type,
			HMODULE software,
			UINT flags,
			const D3D_FEATURE_LEVEL* pLevels,
			UINT numLevels,
			UINT sdkVersion);
		Direct3DDevice(CComPtr<ID3D11Device> dev);
	private:
		D3D_FEATURE_LEVEL activeLevel;
		CComPtr<ID3D11Device> pDev;
		CComPtr<ID3D11DeviceContext> pCtx;
	};
}
#pragma once
#include "stdafx.h"
#include <memory>
namespace LibCommon {
	class Direct3DRenderer {
	public:
		Direct3DRenderer();
		Direct3DRenderer(
			IDXGIAdapter* pAdapter,
			D3D_DRIVER_TYPE type,
			HMODULE software,
			UINT flags,
			const D3D_FEATURE_LEVEL* plevels,
			UINT numLevels,
			UINT sdkVersion,
			ID3D11Device** ppDevice,
			D3D_FEATURE_LEVEL* outLevel,
			ID3D11DeviceContext** ppContext
			);
		CComPtr<IDXGIDevice> getDeviceAsDXGI();
		CComPtr<ID3D11Device> getDevice();
	private:
		void init(IDXGIAdapter* pAdapter,
			D3D_DRIVER_TYPE type,
			HMODULE software,
			UINT flags,
			const D3D_FEATURE_LEVEL* plevels,
			UINT numLevels,
			UINT sdkVersion,
			ID3D11Device** ppDevice,
			D3D_FEATURE_LEVEL* outLevel,
			ID3D11DeviceContext** ppContext);
		CComPtr<ID3D11Device> m_pDevice;
		CComPtr<ID3D11DeviceContext> m_pContect;
	};
}
#include "stdafx.h"
#include "Direct3DRenderer.h"
using namespace LibCommon;
Direct3DRenderer::Direct3DRenderer() {
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	init(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags, nullptr, 0, D3D11_SDK_VERSION, &m_pDevice, nullptr, &m_pContect);
}

void Direct3DRenderer::init(IDXGIAdapter* pAdapter,
			D3D_DRIVER_TYPE type,
			HMODULE software,
			UINT flags,
			const D3D_FEATURE_LEVEL* plevels,
			UINT numLevels,
			UINT sdkVersion,
			ID3D11Device** ppDevice,
			D3D_FEATURE_LEVEL* outLevel,
			ID3D11DeviceContext** ppContext) {
				HRESULT hr =  D3D11CreateDevice(pAdapter, type, software, flags, plevels, numLevels, sdkVersion, ppDevice, outLevel, ppContext);
				if(FAILED(hr)) {
					throw hr;
				}
}

Direct3DRenderer::Direct3DRenderer(
			IDXGIAdapter* pAdapter,
			D3D_DRIVER_TYPE type,
			HMODULE software,
			UINT flags,
			const D3D_FEATURE_LEVEL* plevels,
			UINT numLevels,
			UINT sdkVersion,
			ID3D11Device** ppDevice,
			D3D_FEATURE_LEVEL* outLevel,
			ID3D11DeviceContext** ppContext) {
				init(pAdapter, type, software, flags, plevels, numLevels, sdkVersion, ppDevice, outLevel, ppContext);
}

CComPtr<IDXGIDevice> Direct3DRenderer::getDeviceAsDXGI() {
	CComPtr<IDXGIDevice> retval;
	HRESULT hr = m_pDevice.QueryInterface(&retval);
	if(FAILED(hr)) {
		throw hr;
	}
	return retval;
}
CComPtr<ID3D11Device> Direct3DRenderer::getDevice() {
	return m_pDevice;
}


#pragma once
#include "stdafx.h"
#include <LibDXGI/LibDXGI.h>
#include <memory>
#include <LibCommon/IRenderer.h>
#include "Direct3DRenderingMessage.h"
namespace LibDirect3D {
	class Direct3DRenderer : public LibCommon::IRenderer {
	public:
		Direct3DRenderer();
		virtual LibCommon::IMessage * getRenderingMessage() override;
	private:
		
		void init(IDXGIAdapter* pAdapter,
			D3D_DRIVER_TYPE type,
			HMODULE software,
			UINT flags,
			const D3D_FEATURE_LEVEL* plevels,
			UINT numLevels,
			UINT sdkVersion,
			D3D_FEATURE_LEVEL* outLevel);
		
		void bindToHwnd(HWND target);


		CComPtr<ID3D11Device1> m_pDevice;
		CComPtr<ID3D11DeviceContext1> m_pContext;
		CComPtr<IDXGISwapChain1> m_pSwapChain;
		CComPtr<IDXGIFactory2> m_pDXGIFactory;
		CComPtr<IDXGIDevice2> m_pDXGIDevice;

		std::unique_ptr<Direct3DRenderingMessage> lazyMessage;
	};
}
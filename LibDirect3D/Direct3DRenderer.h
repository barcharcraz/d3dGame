#pragma once
#include "stdafx.h"
#include <LibDXGI/LibDXGI.h>
#include <LibCommon/IRenderer.h>
#include "Direct3DRenderingMessage.h"
namespace LibDirect3D {
	class Direct3DRenderer : public LibCommon::IRenderer {
	public:
		Direct3DRenderer();
		virtual LibCommon::IMessage * getRenderingMessage() override;

		void addPixelShader(ID3D11Device * pDev, const std::string &name, const BYTE shaderBlob[], const std::vector<D3D11_INPUT_ELEMENT_DESC> &desc);
		void addVertexShader(ID3D11Device * pDev, const std::string &name, const BYTE shaderBlob[], const std::vector<D3D11_INPUT_ELEMENT_DESC> &desc);
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

		CComPtr<ID3D11Device2> m_pDevice;
		CComPtr<ID3D11DeviceContext2> m_pContext;
		CComPtr<IDXGISwapChain2> m_pSwapChain;
		CComPtr<IDXGIFactory2> m_pDXGIFactory;
		CComPtr<IDXGIDevice3> m_pDXGIDevice;

		

		std::unique_ptr<Shaders> m_pShaders;
		std::unique_ptr<Direct3DRenderingMessage> lazyMessage;
	};
}
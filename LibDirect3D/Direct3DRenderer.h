#pragma once
#include "stdafx.h"
#include <LibDXGI/LibDXGI.h>
#include <LibCommon/IRenderer.h>
#include "Direct3DRenderingMessage.h"
#include "DataFormats.h"
namespace LibDirect3D {
	class Direct3DRenderer : public LibCommon::IRenderer {
	public:
		Direct3DRenderer();
		Direct3DRenderer(HWND target);
		virtual LibCommon::IMessage * getRenderingMessage() override;

		void addPixelShader(const std::string &name, const BYTE shaderBlob[], size_t shaderSize, const std::vector<D3D11_INPUT_ELEMENT_DESC> &desc);
		void addVertexShader(const std::string &name, const BYTE shaderBlob[], size_t shaderSize, const std::vector<D3D11_INPUT_ELEMENT_DESC> &desc);

		void addPixelShader(const std::string& filename, const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc);
		void addVertexShader(const std::string& filename, const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc);

		void addPixelShader(const std::string& filename);
		void addVertexShader(const std::string& filename);

		void Present();
		void Clear();
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
		void createRenderTarget();
		void setViewports();
		CComPtr<ID3D11Device2> m_pDevice;
		CComPtr<ID3D11DeviceContext2> m_pContext;
		CComPtr<IDXGISwapChain2> m_pSwapChain;
		CComPtr<IDXGIFactory2> m_pDXGIFactory;
		CComPtr<IDXGIDevice3> m_pDXGIDevice;
		CComPtr<ID3D11RenderTargetView> m_pRenderTarget;
		

		std::unique_ptr<Shaders> m_pShaders;
		std::unique_ptr<Direct3DRenderingMessage> lazyMessage;

		
	};
}
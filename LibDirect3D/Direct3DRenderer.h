#pragma once
#include "stdafx.h"
#include <LibDXGI/LibDXGI.h>
#include <LibCommon/IRenderer.h>
#include <LibComponents/Model.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "DataFormats.h"
namespace LibDirect3D {
	class Direct3DRenderer : public LibCommon::IRenderer {
	public:
		Direct3DRenderer();
		Direct3DRenderer(HWND target);

		void Present();
		void Clear();

		CComPtr<ID3D11Buffer> CreateIndexBuffer(const Components::Model& indexData) const;
		CComPtr<ID3D11Buffer> CreateVertexBuffer(const Components::Model& vertexData) const;
		CComPtr<ID3D11Buffer> GetTransforms(const LibCommon::Transforms& transforms) const;
		CComPtr<ID3D11Buffer> CreateConstantBuffer(const void* data, size_t size) const;
		CComPtr<ID3D11Buffer> CreateConstantBuffer(size_t size) const;
		CComPtr<ID3D11Buffer> CreateStructuredBuffer(size_t structSize, unsigned int length) const;
		CComPtr<ID3D11Buffer> CreateStructuredBuffer(const void* data, size_t structSize, unsigned int length) const;
		void UpdateStructuredBuffer(CComPtr<ID3D11Buffer> buffer, const void* data, size_t size) const;
		void UpdateConstantBuffer(CComPtr<ID3D11Buffer> buffer, const void* data, size_t size) const;
		size_t GetBufferSize(CComPtr<ID3D11Buffer> buffer) const;
		
		CComPtr<ID3D11Device2> pDev;
		CComPtr<ID3D11DeviceContext2> pCtx;
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
		void createDepthStencil();
		void setViewports();
		CComPtr<IDXGISwapChain2> m_pSwapChain;
		CComPtr<IDXGIFactory2> m_pDXGIFactory;
		CComPtr<IDXGIDevice3> m_pDXGIDevice;
		CComPtr<ID3D11RenderTargetView> m_pRenderTarget;

		CComPtr<ID3D11DepthStencilState> _pdsState;
		CComPtr<ID3D11DepthStencilView> _pdsView;
		CComPtr<ID3D11Texture2D> _pDepthStencil;


		mutable CComPtr<ID3D11Buffer> _transformBuffer;

		
	};
}
#pragma once
#include "stdafx.h"
#include "Direct3DRenderingMessage.h"
#include <LibCommon/Data.h>
#include <LibCommon/IComponent.h>
namespace LibDirect3D {
	class ModelRenderer : public LibCommon::IComponent {
	public:
		ModelRenderer(const LibCommon::Model& model);
		virtual void OnConnect() override;
	private:
		void init();
		void handleDraw(Direct3DRenderingMessage * msg);
		shaderSet _activeShaders;
		void initConstantBuffers(ID3D11Device * pDev);
		void initIndexBuffer(ID3D11Device * pDev);
		void initVertexBuffers(ID3D11Device * pDev);
		void updateTransformBuffer(ID3D11DeviceContext * pCtx);
		LibCommon::Transforms transform;
		CComPtr<ID3D11Buffer> _pVertexBuffer;
		CComPtr<ID3D11Buffer> _pIndexBuffer;
		CComPtr<ID3D11Buffer> _pTransformBuffer;
		LibCommon::Model _model;
	};
}
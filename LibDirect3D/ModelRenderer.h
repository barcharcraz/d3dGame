#pragma once
#include "stdafx.h"
#include "Direct3DRenderingMessage.h"
#include <LibCommon/Data.h>
#include <LibCommon/IComponent.h>
namespace LibDirect3D {
	class ModelRenderer : public LibCommon::IComponent {
	public:
		ModelRenderer(const LibCommon::Model& model);
	private:
		void init();
		void handleDraw(Direct3DRenderingMessage * msg);
		shaderSet _activeShaders;
		void initBuffers(ID3D11Device * pDev);
		CComPtr<ID3D11Buffer> _pVertexBuffer;
		CComPtr<ID3D11Buffer> _pIndexBuffer;
		LibCommon::Model _model;
	};
}
#pragma once
#include "stdafx.h"
#include "Direct3DRenderer.h"
#include <LibCommon/Data.h>
#include <LibCommon/Entity.h>
#include <LibCommon/System.h>
#include <LibComponents/Model.h>
namespace LibDirect3D {
	class ModelRenderer : public LibCommon::System {
	public:
		explicit ModelRenderer(const Direct3DRenderer& renderer);
		virtual void Process(LibCommon::Entity * e) override;
		virtual void Init() override;
	private:
		void init();
		shaderSet _activeShaders;
		void createConstantBuffers();
		CComPtr<ID3D11Buffer> createIndexBuffer(const Components::Model& model);
		CComPtr<ID3D11Buffer> createVertexBuffer(const Components::Model& model);
		void updateTransformBuffer(const Components::Transform3D& transform);
		LibCommon::Transforms constTransforms;
		const Eigen::Matrix4f* cameraTransform;
		CComPtr<ID3D11Buffer> _pTransformBuffer;

		CComPtr<ID3D11Device2> pDev;
		CComPtr<ID3D11DeviceContext2> pCtx;
	};
}
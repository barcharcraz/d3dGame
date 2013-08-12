#pragma once
#include "stdafx.h"
#include "Direct3DRenderer.h"
#include <LibCommon/Data.h>
#include <LibCommon/Entity.h>
#include <LibCommon/System.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Model.h>
#include <map>
namespace LibDirect3D {
	class ModelRenderer : public LibCommon::System {
	public:
		explicit ModelRenderer(const Direct3DRenderer& renderer);
		virtual void Process(LibCommon::Entity * e) override;
		virtual void Init() override;
		virtual void OnEntityRemove(LibCommon::Entity* e) override;
	private:
		struct res {
			CComPtr<ID3D11Buffer> indexBuffer;
			CComPtr<ID3D11Buffer> vertexBuffer;
		};
		void init();
		LibCommon::Transforms constTransforms;
		Eigen::Matrix4f cameraTransform;
		std::map<LibCommon::Entity*, res> entityCache;
		const Direct3DRenderer* render;
	};
}
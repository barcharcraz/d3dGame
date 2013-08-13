#pragma once
#include "stdafx.h"
#include "Direct3DRenderer.h"
#include <LibCommon/Data.h>
#include <LibCommon/Entity.h>
#include <LibCommon/System.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Model.h>
#include <LibComponents/DirectionalLight.h>
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
		struct light {

		};
		void init();
		std::vector<Components::DirectionalLight*> directionalLights;
		LibCommon::Transforms constTransforms;
		Eigen::Matrix4f cameraTransform;
		Eigen::Matrix4f camPos;
		CComPtr<ID3D11Buffer> _lights;
		std::map<LibCommon::Entity*, res> entityCache;
		const Direct3DRenderer* render;
	};
}
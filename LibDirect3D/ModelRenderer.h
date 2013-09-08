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
#include "Direct3DTexture.h"
namespace LibDirect3D {
	class ModelRenderer : public LibCommon::System {
	public:
		explicit ModelRenderer(Direct3DRenderer* renderer);
		virtual void Process(LibCommon::Entity * e) override;
		virtual void PreProcess() override;
		virtual void OnEntityRemove(LibCommon::Entity* e) override;
	private:
		struct res {
			CComPtr<ID3D11Buffer> indexBuffer;
			CComPtr<ID3D11Buffer> vertexBuffer;
		};
		std::vector<Components::DirectionalLight*> directionalLights;
		LibCommon::Transforms constTransforms;
		Eigen::Matrix4f cameraTransform;
		Eigen::Matrix4f camPos;
		CComPtr<ID3D11Buffer> _lights;
		CComPtr<ID3D11Buffer> _materials;
		std::map<LibCommon::Entity*, res> entityCache;
		std::unordered_map<LibCommon::Entity*, Direct3DTexture> texCache;
		Direct3DRenderer* render;
		CComPtr<ID3D11ShaderResourceView> _pointLights;
		CComPtr<ID3D11ShaderResourceView> _dirLights;
		void initPointLights();
		void initDirLights();
	};
}
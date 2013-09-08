#pragma once
#include <LibCommon/System.h>
#include "Direct3DRenderer.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <unordered_map>
#include "Direct3DTexture.h"
namespace LibDirect3D {
	class BillboardRenderer : public LibCommon::System {
	public:
		explicit BillboardRenderer(Direct3DRenderer* renderer);
		virtual void Process(LibCommon::Entity* e) override;
		virtual void PreProcess() override;
		virtual void OnEntityRemove(LibCommon::Entity* e) override;
	private:
		struct res {
			CComPtr<ID3D11Buffer> indexBuf;
			CComPtr<ID3D11Buffer> vertexBuf;
		};
		std::unordered_map<LibCommon::Entity*, res> entCache;
		std::unordered_map<LibCommon::Entity*, Direct3DTexture> texCache;
		Eigen::Matrix4f view;
		Eigen::Matrix4f proj;
		Direct3DRenderer* render;
	};
}
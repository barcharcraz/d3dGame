#pragma once
#include <LibCommon/System.h>
#include "Direct3DRenderer.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace LibDirect3D {
	class BillboardRenderer : public LibCommon::System {
	public:
		explicit BillboardRenderer(const Direct3DRenderer& renderer);
		virtual void Process(LibCommon::Entity* e) override;
		virtual void PreProcess() override;
		virtual void OnEntityRemove(LibCommon::Entity* e) override;
	private:
		Eigen::Matrix4f view;
		Eigen::Matrix4f proj;
		const Direct3DRenderer& render;
	};
}
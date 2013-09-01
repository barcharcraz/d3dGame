#include "stdafx.h"
#include "BillboardRenderer.h"
#include <LibCommon/Scene.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Camera.h>
namespace LibDirect3D {
	BillboardRenderer::BillboardRenderer(const Direct3DRenderer& renderer)
		: render(renderer) 
	{

	}
	void BillboardRenderer::PreProcess() {
		auto camera = parent->SelectEntity({ typeid(Components::Camera), typeid(Components::Transform3D) });
		view = camera->Get<Components::Transform3D>()->transform.matrix();
		proj = camera->Get<Components::Camera>()->CameraMatrix;

	}
}

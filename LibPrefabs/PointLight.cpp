#include "stdafx.h"
#include "PointLight.h"
#include <LibComponents/Transform.h>
#include <LibComponents/PointLight.h>
namespace Prefabs {
	PointLight::PointLight(const Eigen::Vector3f& pos, const Eigen::Vector4f& color) {
		AddComponent<Components::Transform3D>(Eigen::Affine3f(Eigen::Translation3f(pos)));
		AddComponent<Components::PointLight>(color);
	}
}
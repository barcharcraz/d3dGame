#include "stdafx.h"
#include "Camera.h"
#include <memory>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <LibComponents/Camera.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Velocity.h>
namespace Prefabs {
	Camera::Camera() {
		namespace comp = Components;
		AddComponent(std::make_unique<comp::Camera>());
		AddComponent(std::make_unique<comp::Transform3D>(Eigen::Affine3f::Identity()));
		AddComponent(std::make_unique<comp::PremulVelocity3D>(Eigen::Affine3f::Identity()));
	}
}
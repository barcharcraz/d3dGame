#include "Crosshair.h"
#include <Components2D.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace Prefabs {
	Crosshair::Crosshair() {
		AddComponent<Components::Circle>(Eigen::Vector2f{ 0.0f, 0.0f }, 0.1f);
		AddComponent<Components::Transform2D>(Eigen::Affine2f::Identity());
	}
}
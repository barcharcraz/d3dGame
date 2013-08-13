#include "DirectionalLight.h"
#include <LibComponents/DirectionalLight.h>
namespace Prefabs {
	DirectionalLight::DirectionalLight(const Eigen::Vector4f& color, const Eigen::Vector3f& dir) {
		AddComponent<Components::DirectionalLight>(color, dir);
	}
}
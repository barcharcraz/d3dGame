#include "DirectionalLight.h"
#include <LibComponents/DirectionalLight.h>
#include <LibComponents/Transform.h>
namespace Prefabs {
	DirectionalLight::DirectionalLight(const Eigen::Vector4f& color, const Eigen::Vector3f& dir) {
		using namespace Eigen;
		Eigen::Vector4f newDir;
		newDir << dir, 1;
		AddComponent<Components::DirectionalLight>(color, newDir);
	}
}
#include "DirectionalLight.h"
#include <LibComponents/DirectionalLight.h>
#include <LibComponents/Transform.h>
namespace Prefabs {
	DirectionalLight::DirectionalLight(const Eigen::Vector4f& color, const Eigen::Vector3f& dir) {
		using namespace Eigen;
		AddComponent<Components::DirectionalLight>(color, dir);
		AddComponent<Components::Transform3D>(Affine3f(Quaternionf::FromTwoVectors(Vector3f::UnitY(), dir)));
	}
}
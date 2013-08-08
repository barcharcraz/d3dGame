#include "StaticModel.h"
#include <LibComponents/Transform.h>
#include <LibComponents/Shaders.h>
namespace Prefabs {
	StaticModel::StaticModel(const Components::Model& mod, const Components::Texture& tex) {
		AddComponent<Components::Transform3D>(Eigen::Affine3f::Identity());
		AddComponent<Components::Model>(mod);
		AddComponent<Components::Texture>(tex);
	}
}
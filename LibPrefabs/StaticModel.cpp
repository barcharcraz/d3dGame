#include "StaticModel.h"
#include <LibComponents/Transform.h>
#include <LibComponents/Shaders.h>
#include <LibComponents/Effect.h>
#include <LibEffects/EffectsManagement.h>
namespace Prefabs {
	StaticModel::StaticModel(const Components::Model& mod, const Components::Texture& tex) {
		using Effects::ShaderCaps;
		AddComponent<Components::Transform3D>(Eigen::Affine3f::Identity());
		AddComponent<Components::Model>(mod);
		AddComponent<Components::Texture>(tex);
		AddComponent<Components::Effect>(Effects::ChooseEffect({ ShaderCaps::LIT_DIRECTIONAL, ShaderCaps::MESH_INDEXED, ShaderCaps::TEXTURE_MAPPED }));
	}
}
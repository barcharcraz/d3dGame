#include "StaticModel.h"
#include <LibComponents/Transform.h>
#include <LibComponents/Shaders.h>
#include <LibComponents/Effect.h>
#include <LibComponents/Material.h>
#include <LibEffects/EffectsManagement.h>
#include <LibComponents/AxisAlignedBB.h>
namespace Prefabs {
	StaticModel::StaticModel(const Components::Model& mod, const Components::Texture& tex) {
		using Effects::ShaderCaps;
		AddComponent<Components::Transform3D>(Eigen::Affine3f::Identity());
		AddComponent<Components::Model>(mod);
		AddComponent<Components::Texture>(tex);
		AddComponent<Components::Effect>(Effects::ChooseEffect({ ShaderCaps::LIT_DIRECTIONAL, ShaderCaps::MESH_INDEXED, ShaderCaps::TEXTURE_MAPPED }));
		AddComponent<Components::Material>(
			Eigen::Vector4f(0.1f, 0.1f, 0.1f, 1.0f),
			Eigen::Vector4f(0.5f, 0.5f, 0.5f, 1.0f), 
			Eigen::Vector4f(0.5f, 0.5f, 0.5f, 1.0f),
			1.0f);
		AddComponent<Components::AxisAlignedBB>(Eigen::AlignedBox3f{});
	}
}

#include "SkyDome.h"
#include <LibEffects/EffectsManagement.h>
#include <RenderingUtils/ModelProcessing.h>
#include <Components.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace Prefabs {
    SkyDome::SkyDome(float radius, const Components::Texture& tex) {
        using namespace Components;
        using Effects::ShaderCaps;
        AddComponent<Transform3D>(Eigen::Affine3f::Identity());
        AddComponent<Texture>(tex);
        AddComponent<Effect>(Effects::ChooseEffect({
            ShaderCaps::MESH_INDEXED,
            ShaderCaps::TEXTURE_MAPPED
        }));
        AddComponent<Material>(
            Eigen::Vector4f(1.0f, 1.0f, 1.0f, 1.0f),
            Eigen::Vector4f::Zero(),
            Eigen::Vector4f::Zero(),
            0
        );
        AddComponent<Model>(utils::generate_icosahedron(radius));
        
        
        
    }
}

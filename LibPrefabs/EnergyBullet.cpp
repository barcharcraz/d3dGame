#include "EnergyBullet.h"
#include <LibComponents/Billboard.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Velocity.h>
#include <LibComponents/Shaders.h>
#include <LibEffects/EffectsManagement.h>
#include <LibComponents/Projectile.h>
#include <LibComponents/Model.h>
#include <RenderingUtils/ModelProcessing.h>
#include <LibEffects/Effect.h>
#include <LibComponents/Effect.h>
#include <LibComponents/Collision.h>
namespace Prefabs {
	EnergyBullet::EnergyBullet(float width, float height, const Components::Texture& tex, std::chrono::milliseconds lifetime) {
		AddComponent<Components::Texture>(tex);
		AddComponent<Components::Transform3D>(Eigen::Affine3f::Identity());
		AddComponent<Components::Billboard>(width, height);
		AddComponent<Components::Model>(utils::generate_quad(width, height));
		AddComponent<Components::Effect>(Effects::ChooseEffect({Effects::ShaderCaps::RENDER_BILLBOARD}));
		AddComponent<Components::Collision>();
	}
	EnergyBullet::EnergyBullet(float width, float height,
		const Components::Texture& tex,
		const Eigen::Vector3f& vel,
		std::chrono::milliseconds lifetime) 
	{
		using namespace Eigen;
		AddComponent<Components::Texture>(tex);
		AddComponent<Components::Transform3D>(Eigen::Affine3f::Identity());
		AddComponent<Components::Billboard>(width, height);
		AddComponent<Components::Model>(utils::generate_quad(width, height));
		AddComponent<Components::Effect>(Effects::ChooseEffect({ Effects::ShaderCaps::RENDER_BILLBOARD }));
		AddComponent<Components::Velocity3D>(Affine3f(Translation3f(vel)));
		AddComponent<Components::Projectile>(100, lifetime);
		AddComponent<Components::Collision>();
	}
}
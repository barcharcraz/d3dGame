#include "EnergyBullet.h"
#include <LibComponents/Billboard.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Velocity.h>
#include <LibComponents/Shaders.h>
#include <LibEffects/EffectsManagement.h>
#include <LibComponents/Model.h>
#include <RenderingUtils/ModelProcessing.h>
#include <LibEffects/Effect.h>
#include <LibComponents/Effect.h>
namespace Prefabs {
	EnergyBullet::EnergyBullet(float width, float height, const Components::Texture& tex) {
		AddComponent<Components::Texture>(tex);
		AddComponent<Components::Billboard>(width, height);
		AddComponent<Components::Model>(utils::generate_quad(width, height));
		AddComponent<Components::Effect>(Effects::ChooseEffect({Effects::ShaderCaps::RENDER_BILLBOARD}));

	}
}
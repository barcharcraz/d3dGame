#include "stdafx.h"
#include "ProjectileSystem.h"
#include <LibComponents/Collision.h>
#include <LibComponents/Projectile.h>
#include <LibCommon/Scene.h>
namespace Systems {
	ProjectileSystem::ProjectileSystem()
		: System({ typeid(Components::Collision), typeid(Components::Projectile) })
	{

	}
	void ProjectileSystem::Init() {
		EnableUpdate({ typeid(Components::Collision) });
	}
	void ProjectileSystem::OnEntityUpdate(LibCommon::Entity* ent, Components::IComponent* comp) {
		auto collision = ent->Get<Components::Collision>();
		if (collision->with.size() > 0) {
			parent->RemoveEntity(ent);
		}
	}
}
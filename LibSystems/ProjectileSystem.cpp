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
	void ProjectileSystem::OnEntityUpdate(LibCommon::Entity* ent, Components::IComponent*) {
		auto collision = ent->Get<Components::Collision>();
		if (collision->with.size() > 0) {
			parent->RemoveEntity(ent);
		}
	}
	void ProjectileSystem::Process(LibCommon::Entity* ent) {
		using namespace std::chrono;
		auto proj = ent->Get<Components::Projectile>();
		auto delta = parent->FrameDelta();
		auto mdelta = duration_cast<milliseconds>(delta);
		proj->time_to_live -= mdelta;
		if (proj->time_to_live <= milliseconds(0)) {
			parent->RemoveEntity(ent);
		}
	}
}
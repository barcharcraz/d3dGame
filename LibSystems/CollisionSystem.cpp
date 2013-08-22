#include "CollisionSystem.h"
#include <LibCommon/Scene.h>
#include <LibComponents/Collision.h>
#include <LibComponents/AxisAlignedBB.h>
namespace Systems {
	CollisionSystem::CollisionSystem()
		: System({typeid(Components::Collision), typeid(Components::AxisAlignedBB)},
		LibCommon::Priority::HIGH)
	{

	}
	void CollisionSystem::Init() {
		entCache = parent->SelectEntities({ typeid(Components::AxisAlignedBB) });
	}
	void CollisionSystem::OnEntityAdd(LibCommon::Entity* e) {
		if (e->HasAllComponents({ typeid(Components::AxisAlignedBB) })) {
			entCache.push_back(e);
		}
	}
	void CollisionSystem::OnEntityRemove(LibCommon::Entity* e) {
		if (e->HasAllComponents({ typeid(Components::AxisAlignedBB) })) {
			auto itr = std::find(entCache.begin(), entCache.end(), e);
			entCache.erase(itr);
		}
	}
	void CollisionSystem::Process(LibCommon::Entity* ent) {
		auto collision = ent->Get<Components::Collision>();
		auto bbox = ent->Get<Components::AxisAlignedBB>();
		for (auto elm : entCache) {
			auto elmbbox = elm->Get<Components::AxisAlignedBB>();
			if (elmbbox->AABB.intersection(bbox->AABB).volume() != 0) {
				collision->with.push_back(elm);
			}
		}
	}
}
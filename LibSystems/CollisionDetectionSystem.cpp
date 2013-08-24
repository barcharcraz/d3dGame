#include "CollisionDetectionSystem.h"
#include <LibCommon/Scene.h>
#include <LibComponents/Collision.h>
#include <LibComponents/AxisAlignedBB.h>
namespace Systems {
	namespace {

	}
	CollisionDetectionSystem::CollisionDetectionSystem()
		: System({typeid(Components::Collision), typeid(Components::AxisAlignedBB)},
		LibCommon::Priority::HIGH)
	{

	}
	void CollisionDetectionSystem::Init() {
		entCache = parent->SelectEntities({ typeid(Components::AxisAlignedBB), typeid(Components::AxisAlignedBBUpdate) });
	}
	void CollisionDetectionSystem::OnEntityAdd(LibCommon::Entity* e) {
		if (e->HasAllComponents({ typeid(Components::AxisAlignedBB) })) {
			entCache.push_back(e);
		}
	}
	void CollisionDetectionSystem::OnEntityRemove(LibCommon::Entity* e) {
		if (e->HasAllComponents({ typeid(Components::AxisAlignedBB) })) {
			auto itr = std::find(entCache.begin(), entCache.end(), e);
			entCache.erase(itr);
		}
	}
	void CollisionDetectionSystem::Process(LibCommon::Entity* ent) {
		auto collision = ent->Get<Components::Collision>();
		auto bbox = ent->Get<Components::AxisAlignedBB>();
		for (auto elm : entCache) {
			auto elmbbox = elm->Get<Components::AxisAlignedBB>();
			auto intersection = elmbbox->CurAABB.exteriorDistance(bbox->CurAABB);
			if (ent != elm && intersection == 0) {
				collision->with.push_back(elm);
			}
		}
	}
}
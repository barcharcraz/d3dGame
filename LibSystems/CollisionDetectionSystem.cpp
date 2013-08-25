#include "CollisionDetectionSystem.h"
#include <LibCommon/Scene.h>
#include <LibComponents/Collision.h>
#include <LibComponents/AxisAlignedBB.h>
namespace Systems {
	namespace {

	}
	CollisionDetectionSystem::CollisionDetectionSystem()
		: System({typeid(Components::Collision), typeid(Components::AxisAlignedBB), typeid(Components::AxisAlignedBBUpdate)},
		LibCommon::Priority::HIGH)
	{

	}
	void CollisionDetectionSystem::Init() {
		auto ents = parent->SelectEntities({ typeid(Components::AxisAlignedBB) });
		for (auto elm : ents) {
			sap.AddObject(elm->Get<Components::AxisAlignedBB>()->CurAABB, elm);
		}
	}
	void CollisionDetectionSystem::OnEntityAdd(LibCommon::Entity* e) {
		if (e->HasAllComponents({ typeid(Components::AxisAlignedBB) })) {
			sap.AddObject(e->Get<Components::AxisAlignedBB>()->CurAABB, e);
		}
	}
	void CollisionDetectionSystem::OnEntityRemove(LibCommon::Entity* e) {
		if (e->HasAllComponents({ typeid(Components::AxisAlignedBB) })) {
			sap.RemoveObject(e);
		}
	}
	void CollisionDetectionSystem::Process(LibCommon::Entity* ent) {
		auto collision = ent->Get<Components::Collision>();
		auto bbox = ent->Get<Components::AxisAlignedBB>();
		sap.UpdateObject(bbox->CurAABB, ent);
		auto collidedEnts = sap.QueryObject(ent);
		for (auto elm : collidedEnts) {
			LibCommon::Entity* e = (LibCommon::Entity*) elm;
			collision->with.push_back(e);
			auto otherCollision = e->GetOptional<Components::Collision>();
			otherCollision->with.push_back(ent);
			e->AddEvent<Components::CollisionUpdate>();
		}
		ent->AddEvent<Components::CollisionUpdate>();
	}
}
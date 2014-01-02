#include "CollisionDetectionSystem.h"
#include <LibCommon/Scene.h>
#include <LibComponents/Collision.h>
#include <LibComponents/AxisAlignedBB.h>
namespace Systems {
	namespace {

	}
	CollisionDetectionSystem::CollisionDetectionSystem()
		: System({ typeid(Components::AxisAlignedBB) },
		LibCommon::Priority::MEDIUM)
	{
		
	}
	void CollisionDetectionSystem::Init() {
		EnableUpdate({ typeid(Components::AxisAlignedBB) });
	}
	void CollisionDetectionSystem::OnEntityAdd(LibCommon::Entity* e) {
	    sap.AddObject(e->Get<Components::AxisAlignedBB>()->CurAABB, e);
	}
	void CollisionDetectionSystem::OnEntityRemove(LibCommon::Entity* e) {
		sap.RemoveObject(e);
	}
	void CollisionDetectionSystem::OnEntityUpdate(LibCommon::Entity* ent, Components::IComponent*) {
		auto bbox = ent->Get<Components::AxisAlignedBB>();
		sap.UpdateObject(bbox->CurAABB, ent);
		auto collidedEnts = sap.QueryObject(ent);
		auto collision = ent->GetOptional<Components::Collision>();
		for (auto elm : collidedEnts) {
			LibCommon::Entity* e = (LibCommon::Entity*) elm;
			if (e != ent) {
				if (collision) {
					collision->with.push_back(e);
				}
				Components::Collision* otherCollision = e->GetOptional<Components::Collision>();
				if (otherCollision) {
					otherCollision->with.push_back(ent);
					NotifyUpdate(e, otherCollision);
				}
			}
		}
		//NotifyUpdate(ent, collision);
	}
}
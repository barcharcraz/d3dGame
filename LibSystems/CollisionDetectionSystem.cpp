#include "CollisionDetectionSystem.h"
#include <LibCommon/Scene.h>
#include <LibComponents/Collision.h>
#include <LibComponents/AxisAlignedBB.h>
#include <typeinfo>
namespace Systems {
	using namespace sparse::ecs;
	namespace {

	}
	CollisionDetectionSystem::CollisionDetectionSystem()
	{
		write_comp = Components::Collision::stype.type;
		state_comp = sparse::ecs::GenID(typeid(state));
		update_func = &CollisionDetectionSystem::CollisionUpdate;
	}
	void CollisionDetectionSystem::Init() {
		EnableUpdate({ typeid(Components::AxisAlignedBB) });
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
	void CollisionDetectionSystem::CollisionUpdate(Row* state, const Scene* scene, Row* out) {
		if (state->size() == 0) {
			state->push_back(CollisionDetectionSystem::state{});
		}
		auto tstate = MakeAdapter<CollisionDetectionSystem::state>(*state);
		Physics::SweepAndPrune& sap = tstate.EntityComp(0).sap;
	}
}
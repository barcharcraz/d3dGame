#include "SimpleCollisionSystem.h"
#include <LibComponents/Velocity.h>
#include <LibComponents/Collision.h>
#include <LibComponents/Transform.h>
#include <LibComponents/AxisAlignedBB.h>
#include <algorithm>
#include <vector>
namespace Systems {
	SimpleCollisionSystem::SimpleCollisionSystem()
		: System({ typeid(Components::Velocity3D),
		typeid(Components::Transform3D),
		typeid(Components::AxisAlignedBB),
		typeid(Components::Collision) })
	{
		priority = LibCommon::Priority::LOW;
	}
	void SimpleCollisionSystem::Init() {
		EnableUpdate({ typeid(Components::Collision) });
	}
	void SimpleCollisionSystem::OnEntityUpdate(LibCommon::Entity* ent, Components::IComponent* comp) {
		auto collisions = ent->Get<Components::Collision>();
		auto velocity = ent->Get<Components::Velocity3D>();
		auto transform = ent->Get<Components::Transform3D>();
		auto thisAABB = ent->Get<Components::AxisAlignedBB>();
		if (collisions->with.size() != 0) {
			auto possiblePos = velocity->velocity * transform->transform;
			for (auto& ents : collisions->with) {
				auto aabb = ents->Get<Components::AxisAlignedBB>();
				auto volume = thisAABB->CurAABB.intersection(aabb->CurAABB).volume();
				auto possibleTransform = thisAABB->CurAABB.translate(velocity->velocity.translation());
				auto possibleVolume = possibleTransform.intersection(aabb->CurAABB).volume();
				if (possibleVolume < volume) {
					velocity->velocity.translation() = Eigen::Vector3f{ 0, 0, 0 };
				}
			}
			collisions->with.clear();
		}
	}
	void SimpleCollisionSystem::Process(LibCommon::Entity* ent) {
		
	}
}
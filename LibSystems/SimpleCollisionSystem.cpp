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
		typeid(Components::Collision) })
	{
		priority = LibCommon::Priority::LOW;
	}
	void SimpleCollisionSystem::Process(LibCommon::Entity* ent) {
		auto collisions = ent->Get<Components::Collision>();
		auto velocity = ent->Get<Components::Velocity3D>();
		auto transform = ent->Get<Components::Transform3D>();
		if (collisions->with.size() != 0) {
			auto possiblePos = velocity->velocity * transform->transform;
			for (auto& ents : collisions->with) {
				auto aabb = ents->Get<Components::AxisAlignedBB>();
				auto curDist = aabb->CurAABB.center() - transform->transform.translation();
				auto cur = curDist.norm();
				auto possibleDist = aabb->CurAABB.center() - possiblePos.translation();
				auto next = possibleDist.norm();
				if (next < cur) {
					velocity->velocity.translation() = Eigen::Vector3f{ 0, 0, 0 };
				}
			}
			collisions->with.clear();
		}
	}
}
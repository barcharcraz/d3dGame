#include "SimpleCollisionSystem.h"
#include <LibComponents/Velocity.h>
#include <LibComponents/Collision.h>
#include <algorithm>
#include <vector>
namespace Systems {
	SimpleCollisionSystem::SimpleCollisionSystem()
		: System({ typeid(Components::Velocity3D), typeid(Components::Collision) })
	{
		priority = LibCommon::Priority::LOW;
	}
	void SimpleCollisionSystem::Process(LibCommon::Entity* ent) {
		auto collisions = ent->Get<Components::Collision>();
		auto velocity = ent->Get<Components::Velocity3D>();
		if (collisions->with.size() != 0) {
			velocity->velocity.translation() = Eigen::Vector3f{ 0, 0, 0 };
			collisions->with.clear();
		}
	}
}
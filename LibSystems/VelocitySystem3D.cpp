#include "stdafx.h"
#include "VelocitySystem3D.h"
#include <LibComponents/Velocity.h>
#include <LibComponents/Transform.h>
namespace Systems {
    using namespace Components;
	using namespace LibCommon;
	VelocitySystem3D::VelocitySystem3D() : System({ typeid(Velocity3D), typeid(Transform3D) }) {

	}
	void VelocitySystem3D::Process(Entity* e) {
		auto& transform = e->Get<Transform3D>()->transform;
		auto& velocity = e->Get<Velocity3D>()->velocity;
		if (velocity.matrix() != velocity.Identity().matrix()) {
            transform = transform * velocity;
			NotifyUpdate(e, e->Get<Transform3D>());
		}
	}
}

#include "stdafx.h"
#include "VelocitySystem3D.h"
#include <LibComponents/Velocity.h>
#include <LibComponents/Transform.h>
namespace LibCommon {
    using namespace Components;
	VelocitySystem3D::VelocitySystem3D() : System({ typeid(Velocity3D), typeid(Transform3D) }) {

	}
	void VelocitySystem3D::Process(Entity* e) {
		auto transform = e->Get<Transform3D>();
		auto velocity = e->Get<Velocity3D>();
		transform->transform = transform->transform * velocity->velocity;
	}
}

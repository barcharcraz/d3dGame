#include "PremulVelocitySystem3D.h"
#include <LibComponents/Velocity.h>
#include <LibComponents/Transform.h>
namespace Systems {
    using namespace Components;
    PremulVelocitySystem3D::PremulVelocitySystem3D()
        : System({ typeid(PremulVelocity3D), typeid(Transform3D) }) {}

    void PremulVelocitySystem3D::Process(LibCommon::Entity* e) {
        auto transform = e->Get<Transform3D>();
        auto velocity = e->Get<PremulVelocity3D>();
		transform->position += velocity->linear;
		transform->rotation = transform->rotation * velocity->angular;
        NotifyUpdate(e, e->Get<Transform3D>());
    }
}
#include "Collision.h"

namespace Components {
    sparse::ecs::ComponentType Collision::stype = sparse::ecs::GenID();
	Collision::Collision()
	{
        size = sizeof(Collision);
        type = Collision::stype;
	}
}

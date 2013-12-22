#include "Collision.h"

namespace Components {
    sparse::ecs::ComponentInfo Collision::stype = sparse::ecs::GenDefCompInfo<Collision>();
	Collision::Collision()
	{
        info = &Collision::stype;
	}
}

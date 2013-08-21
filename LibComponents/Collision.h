#ifndef LIBCOMPONENTS_COLLISION_H
#define LIBCOMPONENTS_COLLISION_H
#include "IComponent.h"
#include <LibCommon/Entity.h>
namespace Components {
	class Collision {
	public:
		Collision(LibCommon::Entity* const with_arg);
		LibCommon::Entity* const with;
	};
}

#endif
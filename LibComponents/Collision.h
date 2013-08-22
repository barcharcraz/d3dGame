#ifndef LIBCOMPONENTS_COLLISION_H
#define LIBCOMPONENTS_COLLISION_H
#include "IComponent.h"
#include <LibCommon/Entity.h>
#include <vector>
namespace Components {
	class Collision {
	public:
		Collision();
		std::vector<LibCommon::Entity*> with;
	};
}

#endif
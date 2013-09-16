#ifndef LIBCOMPONENTS_COLLISION_H
#define LIBCOMPONENTS_COLLISION_H
#include "IComponent.h"
#include <LibCommon/Entity.h>
#include <vector>
#include <Utils/event.h>
namespace Components {
	class Collision : public IComponent {
	public:
		Collision();
		std::vector<LibCommon::Entity*> with;
	};
	class CollisionUpdate : public IComponent {};
	
}

#endif
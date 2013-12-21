#ifndef LIBCOMPONENTS_COLLISION_H
#define LIBCOMPONENTS_COLLISION_H
#include <ecs.h>
#include <vector>
#include <Utils/event.h>
namespace Components {
	class Collision : public sparse::ecs::Component {
	public:
        static sparse::ecs::ComponentType stype;
		Collision();
		std::vector<sparse::ecs::Entity> with;
	};
	
}

#endif

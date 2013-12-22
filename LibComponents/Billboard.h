#ifndef LIBCOMPONENTS_BILLBOARD_H
#define LIBCOMPONENTS_BILLBOARD_H
#include <ecs.h>
namespace Components {
	class Billboard : public sparse::ecs::Component {
	public:
        static sparse::ecs::ComponentInfo stype;
		Billboard(float width_arg, float height_arg);
		float width;
		float height;
	};
}

#endif

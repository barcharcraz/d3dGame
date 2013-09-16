#ifndef LIBCOMPONENTS_BILLBOARD_H
#define LIBCOMPONENTS_BILLBOARD_H
#include "IComponent.h"
namespace Components {
	class Billboard : public IComponent {
	public:
		Billboard(float width_arg, float height_arg);
		float width;
		float height;
	};
}

#endif
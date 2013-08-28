#ifndef LIBCOMPONENTS_BILLBOARD_H
#define LIBCOMPONENTS_BILLBOARD_H
#include "IComponent.h"
namespace Components {
	class Billboard : public IComponent {
	public:
		float width;
		float height;
	};
}

#endif
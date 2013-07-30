#ifndef LIBCOMPONENTS_ICOMPONENT_H
#define LIBCOMPONENTS_ICOMPONENT_H
#include "stdafx.h"
#include <functional>

namespace Components {
	//IComponent is trivial
	class IComponent {
	public:
		virtual ~IComponent() = 0;
	};
	inline IComponent::~IComponent() {}
}
#endif

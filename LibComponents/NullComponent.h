#ifndef LIBCOMPONENTS_NULLCOMPONENT_H
#define LIBCOMPONENTS_NULLCOMPONENT_H
#include "IComponent.h"

namespace Components {
	//!\brief the null component will never be added to
	//! any entities, this is useful if we would like a system
	//! to not run
	class NullComponent final : public IComponent {
	public:
		virtual ~NullComponent() = 0;
	};
}

#endif
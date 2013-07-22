#ifndef LIBCOMMON_ICOMPONENT_H
#define LIBCOMMON_ICOMPONENT_H
#include "stdafx.h"
#include "Event.h"
#include <functional>

namespace LibCommon {
	class Event;
	class IComponent {
	public:

		Event * messenger;
		virtual ~IComponent() = 0;
	};

	inline IComponent::~IComponent() {};
}
#endif

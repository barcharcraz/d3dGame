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
		//! \brief called when this component is
		//! connected to an entity, in particular
		//! this is called after messenger is connected
		//! to the Entities messenger
		virtual void OnConnect() {};
		virtual ~IComponent() = 0;
	};

	inline IComponent::~IComponent() {};
}
#endif

#ifndef LIBCOMMON_ICOMPONENT_H
#define LIBCOMMON_ICOMPONENT_H

#include "IMessage.h"
#include <boost/signals2.hpp>
namespace LibCommon {
	class IMessage;
	class IComponent {
	public:
		boost::signals2::signal<void(IMessage&)> send;
		boost::signals2::signal<void(IMessage&)> receive;
		virtual ~IComponent() = 0;
	};
	
	inline IComponent::~IComponent() {}
}
#endif

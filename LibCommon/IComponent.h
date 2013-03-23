#ifndef LIBCOMMON_ICOMPONENT_H
#define LIBCOMMON_ICOMPONENT_H

#include "Messages.h"
#include <boost\signals2.hpp>

namespace LibCommon {
	class IComponent {
	public:
		boost::signals2::signal<void(const IMessage&)> send;
		boost::signals2::signal<void(const IMessage&)> receive;
		virtual ~IComponent() = 0;
	};
}
#endif
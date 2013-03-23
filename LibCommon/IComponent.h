#ifndef LIBCOMMON_ICOMPONENT_H
#define LIBCOMMON_ICOMPONENT_H
#include <atomic>
#include "Messages.h"
#include <boost\signals2.hpp>

namespace LibCommon {
	class IComponent {
	public:
		boost::signals2::signal<void(const IMessageHeader&, const IMessageBody&)> send;
		boost::signals2::signal<void(const IMessageHeader&, const IMessageBody&)> receive;
		
	};
}
#endif
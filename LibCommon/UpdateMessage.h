#ifndef LIBCOMMON_UPDATE_H
#define LIBCOMMON_UPDATE_H

#include <memory>
#include <vector>
#include <chrono>
#include "IMessage.h"


namespace LibCommon {
	
	typedef std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> system_duration;
	class UpdateMessage : public IMessage {
	public:
		
		UpdateMessage(system_duration time);
		system_duration tick;
	};
}

#endif
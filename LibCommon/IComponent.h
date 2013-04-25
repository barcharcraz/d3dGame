#ifndef LIBCOMMON_ICOMPONENT_H
#define LIBCOMMON_ICOMPONENT_H

#include "IMessage.h"
#include <boost/signals2.hpp>
namespace LibCommon {
	class IMessage;
	class IComponent {
	public:
		//the reason that these take pointers is because
		//we want to be able to check if casts succeded without
		//handling the std::bad_cast excetpion, this exception
		//will likely get thrown >50% of the time so it is reallyt
		//not that exceptional and avoiding it with pointers (which can equal 0)
		//is a good idea
		boost::signals2::signal<void(IMessage*)> send;
		boost::signals2::signal<void(IMessage*)> receive;
		boost::signals2::connection sendConnection;
		virtual ~IComponent() = 0;

		template<typename T, typename U>
		inline void BindFunction(void (U::*fun)(T*)) {
			//yes this is kinda smelly but it is the best I can do right now
			receive.connect(
				[&](IMessage* msg) {
					if(dynamic_cast<T*>(msg)) {
						this->*fun(dynamic_cast<T>(msg));
					}
			});
		}
	};

	inline IComponent::~IComponent() {}
}
#endif

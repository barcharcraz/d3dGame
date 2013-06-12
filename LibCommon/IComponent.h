#ifndef LIBCOMMON_ICOMPONENT_H
#define LIBCOMMON_ICOMPONENT_H
#include "stdafx.h"
#include "IMessage.h"
#include "Event.hpp"
#include <functional>
#include <boost/signals2.hpp>

namespace LibCommon {
#define COM , //this is horrendus but needed to pas in multiple template parameters to BIND
#define BIND(fun,type) receive.connect([&](LibCommon::IMessage* msg){if(dynamic_cast<type*>(msg)){fun(dynamic_cast<type*>(msg));}})
	class IMessage;
	class IComponent {
	public:
		//the reason that these take pointers is because
		//we want to be able to check if casts succeded without
		//handling the std::bad_cast excetpion, this exception
		//will likely get thrown >50% of the time so it is really
		//not that exceptional and avoiding it with pointers (which can equal 0)
		//is a good idea
		Event<IMessage*> send;
		Event<IMessage*> receive;
		virtual ~IComponent() = 0;

		template<typename T>
		void BindThunk(std::function<void(T)> fun) {
			receive.connect( [&](IMessage* msg){
				if(dynamic_cast<T>(msg)) {
					fun(dynamic_cast<T>(msg));
				}
			});
			
		}
	};

	inline IComponent::~IComponent() {}
}
#endif

#ifndef LIBCOMMON_EVENTS_H
#define LIBCOMMON_EVENTS_H
#include "stdafx.h"
#include <unordered_map>
#include <functional>
#include <typeinfo>
#include <typeindex>
#include "IMessage.h"
#include "Bubbly.h"
#include <LibComponents/IComponent.h>
namespace LibCommon {
	//! \brief this template is a contravarent multicast event
	//!        this means that a function with a parameter of 
	//!        type derived from T can connect to the event
	//!        and any messages that are not of type U are not
	//!        boradcasted to type U, essentailly this does
	//!        the same thing as having a bunch of message types
	//!        defined in this class but without the reqirement
	//!        that you list all the message types beforehand
	//!        do note that for this reason the use of
	//!        dynamic_cast<> is valid and desired, we actually
	//!        want to use RTTI since we are doing something akin
	//!        to calling a virtual function
	class IComponent;
	class Event {
		
	public:
		typedef std::unordered_multimap<std::type_index, std::function<void(IMessage*) > >::const_iterator connection;

		//! \brief register a function to get called on a specific message
		//!        as specified by that functions parameter type
		template<typename T, typename U>
		connection connect(void (T::*func)(U*), T * u) {
			connection rv;
			rv = callbacks.emplace(std::type_index(typeid(U)), [=](IMessage* v){
				(u->*func)(static_cast<U*>(v));
			});
			componentConnections.insert(std::make_pair(static_cast<IComponent*>(u), rv));
			return rv;
		}
		
		void connectForwarder(Event* forwarder);
		void disconnectForwarder(Event* forwarder);
		void disconnect(connection index);
		void disconnect(IComponent* component);
		void send(IMessage * v);
		template<typename T>
		decltype(T::value) Get() {
			T msg;
			send(&msg);
			return msg.value;
		}
		template<typename T>
		decltype(T::value) GetBubbly() {
			T msg;
			Bubbly bmsg(&msg);
			send(&bmsg);
			return msg.value;

		}

	private:
		std::vector<Event*> forwardTargets;
		std::unordered_multimap<IComponent*, connection> componentConnections;
		std::unordered_multimap<std::type_index, std::function<void(IMessage*) > > callbacks;
		//std::list<std::function<void(T*)> > callbacks;
	};
}

#endif

#ifndef LIBCOMMON_EVENTS_HPP
#define LIBCOMMON_EVENTS_HPP
#include "stdafx.h"
#include <list>
#include <functional>
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
	template<typename T>
	class Event {
		
	public:
		typedef typename std::list<std::function<void(T*)> >::const_iterator connection;

		//! \brief register a function to get called on a specific message
		//!        as specified by that functions parameter type
		template<typename U>
		connection connect(std::function<void(U*)> func) {
			callbacks.push_back([func](T* v){
				if(dynamic_cast<U*>(v)) {
					func(dynamic_cast<U*>(v));
				}
			});
			
			return callbacks.cbegin();
		}
		void disconnect(connection index) {
			callbacks.erase(index);
		}
		void operator()(T* v) {
			for(std::function<void(T*)> val : callbacks) {
				val(v);
			}
		}
		void operator()(T && v) {
			this->operator()(&v);
		}
		

	private:
		std::list<std::function<void(T*)> > callbacks;
	};
}

#endif
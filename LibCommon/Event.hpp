#ifndef LIBCOMMON_EVENTS_HPP
#define LIBCOMMON_EVENTS_HPP
#include "stdafx.h"
#include <list>
#include <functional>
namespace LibCommon {
	template<typename T>
	class Event {
		
	public:
		typedef typename std::list<std::function<void(T)> >::const_iterator connection;

		template<typename U>
		connection connect(std::function<void(U)> func) {
			callbacks.push_front([func](T v){
				if(dynamic_cast<U>(v)) {
					func(dynamic_cast<U>(v));
				}
			});
			
			return callbacks.cbegin();
		}
		void disconnect(connection index) {
			callbacks.erase(index);
		}
		void operator()(T v) {
			for(std::function<void(T)> val : callbacks) {
				val(v);
			}
		}
		

	private:
		std::list<std::function<void(T)> > callbacks;
	};
}

#endif
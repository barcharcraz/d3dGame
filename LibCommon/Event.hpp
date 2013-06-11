#ifndef LIBCOMMON_EVENTS_HPP
#define LIBCOMMON_EVENTS_HPP
#include "stdafx.h"
#include <vector>
#include <functional>
namespace LibCommon {
template<typename T>
	class Event<T> {
	public:
		template<typename U>
		int connect<U>(std::function<void(U)> func) {
			int retval = callbacks.size();
			callbacks.push_back([](T v){
				if(dynamic_cast<U>(v)) {
					func(dynamic_cast<U>(v));
				}
			});
			return retval;
		}
	private:
		std::vector<std::function<void(T)> > callbacks;
	};
}

#endif
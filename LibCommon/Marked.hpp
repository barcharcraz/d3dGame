#ifndef LIBCOMMON_MARKED_H
#define LIBCOMMON_MARKED_H
#include "IMessage.h"
namespace LibCommon {
	template<typename T, typename V>
	class Marked : public V {
	public:
		template<typename B>
		Marked(B && arg) : V(std::forward<B>(arg)) {

		}
	};
}

#endif
#ifndef H_LIBCOMMON_GET
#define H_LIBCOMMON_GET
#include "IMessage.h"
#include <LibComponents/IComponent.h>
namespace LibCommon {
	template<typename T>
	class Get : public IMessage {
	public:
		//the value that we got if any.
		//could be null
		T * value;

		//template stuff, do not remove
		typedef T value_type;
	};
}
#endif

#ifndef H_LIBCOMMON_GET
#define H_LIBCOMMON_GET
#include "IMessage.h"
#include "IComponent.h"
namespace LibCommon {
	template<typename T, typename V>
	class Get : public IMessage {
	public:
		Get(IComponent* component);
		//the value that we got if any.
		//could be null
		V * value;
	};

	template<typename T, typename V>
	Get<T, V>::Get(IComponent* component)
	{
		src = component;
	}
}
#endif
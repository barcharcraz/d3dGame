#ifndef H_LIBCOMMON_GET
#define H_LIBCOMMON_GET
#include "IMessage.h"
#include "IComponent.h"
namespace LibCommon {
	template<typename T>
	class Get : public IMessage {
	public:
		Get(IComponent* component);
		//the value that we got if any.
		//could be null
		T * value;
	};

	template<typename T>
	Get<T>::Get(IComponent* component)
	{
		src = component;
	}
}
#endif
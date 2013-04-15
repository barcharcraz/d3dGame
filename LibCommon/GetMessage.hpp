#ifndef H_LIBCOMMON_GITMESSAGE
#define H_LIBCOMMON_GITMESSAGE
#include "IMessage.h"
#include "IComponent.h"
namespace LibCommon {
	template<typename T>
	class GetMessage public IMessage {
	public:
		GetMessage(IComponent* component);
	};

	GetMessage::GetMessage(IComponent* component) 
		: src(component)
	{
	}
#endif
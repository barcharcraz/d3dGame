#ifndef LIBCOMMON_ENTITY_H
#define LIBCOMMON_ENTITY_H
#include "IComponent.h"
#include <list>
#include "Messages.h"

namespace LibCommon {
	using namespace std;
	class Entity : public IComponent {
	public:
		virtual void removeComponent(IComponent* c);
		virtual void addComponent(IComponent* c);
		virtual void handleMessage(const IMessageHeader& header, const IMessageBody& body);
	private:
		list<IComponent*> Components;

	};
}
#endif
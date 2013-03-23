#ifndef LIBCOMMON_ENTITY_H
#define LIBCOMMON_ENTITY_H
#include "IComponent.h"
#include <list>
#include <functional>
#include "Messages.h"

namespace LibCommon {
	using namespace std;
	class Entity : public IComponent {
	public:
		Entity();
		virtual void removeComponent(IComponent* c);
		virtual void addComponent(IComponent* c);
		virtual void handleMessage(const IMessage& message);
	private:
		std::function<void(const IMessage&)> m_handler;
		list<IComponent*> Components;

	};
}
#endif
#include "stdafx.h"
#include "Entity.h"

namespace LibCommon {
	Entity::Entity() {
		_messenger.connect(&Entity::forwardBubble, this);
	}
	void Entity::AddComponent(IComponent* c) {
		c->messenger = &_messenger;
		c->OnConnect();
		Components.push_back(std::unique_ptr<IComponent>(c));
	}
	void Entity::AddComponent(Entity* e) {
		_messenger.connectForwarder(&e->_messenger);
		AddComponent(static_cast<IComponent*>(e));
	}
	void Entity::AddEntity(Entity* e) {
		AddComponent(e);
	}
	std::unique_ptr<IComponent> Entity::removeComponent(int index) {
		std::unique_ptr<IComponent> retval = nullptr;
		retval = std::move(Components[index]);
		//we dont want the component receving our messages any more
		//so we get the connection and we disconnect it
		
		_messenger.disconnect(retval.get());
		//remove the component by memory location
		Components.erase(Components.begin()+=index);
		return retval;
	}
	//---------PROTECTED-----------
	void Entity::OnConnect() {
		_messenger.connect(&Entity::forwardBubble, this);
	}
	//---------PRIVATE-------------
	void Entity::forwardBubble(Bubbly * msg) {
		if (messenger) {
			messenger->send(msg->message);
		}
	}
}

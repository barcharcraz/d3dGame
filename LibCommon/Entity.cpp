#include "stdafx.h"
#include "Entity.h"

namespace LibCommon {
	Entity::Entity() {
		
	}
	void Entity::addComponent(IComponent* c) {
		c->messenger = &_messenger;
		Components.push_back(std::shared_ptr<IComponent>(c));
		_messenger.connect(&Entity::forwardBubble, this);
	}
	std::shared_ptr<IComponent> Entity::removeComponent(int index) {
		std::shared_ptr<IComponent> retval = nullptr;
		retval = std::move(Components[index]);
		//we dont want the component receving our messages any more
		//so we get the connection and we disconnect it
		
		_messenger.disconnect(retval.get());
		//remove the component by memory location
		Components.erase(Components.begin()+=index);
		return retval;
	}
	//---------PRIVATE-------------
	void Entity::forwardBubble(Bubbly * msg) {
		messenger->send(msg->message);
	}
}

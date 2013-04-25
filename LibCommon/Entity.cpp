#include "stdafx.h"
#include "Entity.h"

namespace LibCommon {
	Entity::Entity() {
		m_handler = [this](IMessage *msg){this->handleMessage(msg);};
	}
	void Entity::addComponent(IComponent* c) {
		c->sendConnection = c->send.connect(m_handler);
		Components.push_back(std::shared_ptr<IComponent>(c));
	}
	std::shared_ptr<IComponent> Entity::removeComponent(int index) {
		std::shared_ptr<IComponent> retval = nullptr;
		retval = std::move(Components[index]);
		//we dont want the component receving our messages any more
		retval->send.disconnect(retval->sendConnection);
		//remove the component by memory location
		Components.erase(Components.begin()+=index);
		return retval;

	}
	void Entity::handleMessage(IMessage* message) {
		//forward the message to all the attached components
		for(std::shared_ptr<IComponent> &c : Components) {
			c->receive(message);
		}
	}
	void Entity::handleMessage(IMessage &message) {
		handleMessage(&message);
	}
}

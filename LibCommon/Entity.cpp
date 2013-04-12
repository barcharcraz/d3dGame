#include "stdafx.h"
#include "Entity.h"
namespace LibCommon {
	Entity::Entity() {
		m_handler = [&](const IMessage& msg){handleMessage(msg);};
	}
	void Entity::addComponent(IComponent* c) {
		c->send.connect(m_handler);
		Components.push_back(c);
	}
	void Entity::removeComponent(IComponent* c) {
		//we dont want the component receving our messages any more
		c->send.disconnect(m_handler);
		//remove the component by memory location
		Components.remove(c);

	}
	void Entity::handleMessage(const IMessage& message) {
		//forward the message to all the attached components
		for(IComponent* c : Components) {
			c->receive(message);
		}
	}
	void Entity::handleMessage(const IMessage * const message) {
		handleMessage(*message);
	}
}
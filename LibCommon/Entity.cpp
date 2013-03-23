#include "stdafx.h"
#include "Entity.h"
namespace LibCommon {
	void Entity::addComponent(IComponent* c) {
		c->send.connect(handleMessage);
		Components.push_back(c);
	}
	void Entity::removeComponent(IComponent* c) {
		//we dont want the component receving our messages any more
		c->send.disconnect(handleMessage);
		//remove the component by memory location
		Components.remove(c);

	}
	void Entity::handleMessage(const IMessageHeader& header, const IMessageBody& body) {
		//forward the message to all the attached components
		for(IComponent* c : Components) {
			c->receive(header,body);
		}
	}
}
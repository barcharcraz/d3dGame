#include "stdafx.h"
#include "Entity.h"

namespace LibCommon {
	Entity::Entity() {
		m_handler = [this](IMessage *msg){this->handleMessage(msg);};
		receive.connect<IMessage*>([this](IMessage* msg){this->handleMessage(msg);});
	}
	void Entity::addComponent(IComponent* c) {
		Connections.push_back(c->send.connect(m_handler));
		Components.push_back(std::shared_ptr<IComponent>(c));
	}
	std::shared_ptr<IComponent> Entity::removeComponent(int index) {
		std::shared_ptr<IComponent> retval = nullptr;
		retval = std::move(Components[index]);
		//we dont want the component receving our messages any more
		//so we get the connection and we disconnect it
		
		retval->send.disconnect(Connections[index]);
		//remove the component by memory location
		Components.erase(Components.begin()+=index);
		Connections.erase(Connections.begin()+=index);
		return retval;

	}
	void Entity::handleMessage(IMessage* message) {
		

		if(dynamic_cast<Bubbly*>(message)) {
			Bubbly* bubbleMsg = dynamic_cast<Bubbly*>(message);
			send(bubbleMsg->message);
		} else {
			//forward the message to all the attached components
			for(std::shared_ptr<IComponent> &c : Components) {
				c->receive(message);
			}
		}
	}
	void Entity::handleMessage(IMessage &message) {
		handleMessage(&message);
	}
}

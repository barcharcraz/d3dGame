#include "stdafx.h"
#include "Scene.h"

namespace LibCommon {
	Scene::Scene(IRenderer* pRenderer) : _pRenderer(pRenderer), _rate(34) {
		receive.connect<IMessage>([this](IMessage* msg){this->send(msg);});
		_lastUpdate = _clock.now();
		
	}
	void Scene::AddEntity(Entity* pEntity) {
		_entities.push_back(std::unique_ptr<Entity>(pEntity));
		send.connect<IMessage>([pEntity](IMessage* msg){pEntity->receive(msg);});
		pEntity->send.connect<IMessage>([this](IMessage* msg){this->receive(msg);});
	}
	void Scene::Update() {
		std::unique_ptr<UpdateMessage> updatemsg;
		if( (_clock.now() - _lastUpdate) > _rate ) {
			auto tickTime = _clock.now() - _lastUpdate;
			updatemsg = make_unique<UpdateMessage>(tickTime);
			_lastUpdate = _clock.now();
			
		}
		IMessage * message;
		for (auto& ptr : _entities) {
			message = _pRenderer->getRenderingMessage();
			if (updatemsg) {
				ptr->handleMessage(updatemsg.get());
			}
			ptr->handleMessage(message);
		}
	}
}
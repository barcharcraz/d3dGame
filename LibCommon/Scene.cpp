#include "stdafx.h"
#include "Scene.h"

namespace LibCommon {
	Scene::Scene(IRenderer* pRenderer) : _pRenderer(pRenderer), _rate(34) {
		receive.connect<IMessage*>([this](IMessage* msg){this->send(msg);});
		_lastUpdate = _clock.now();
		
	}
	void Scene::AddEntity(Entity* pEntity) {
		_entities.push_back(std::unique_ptr<Entity>(pEntity));
		send.connect<IMessage*>([pEntity](IMessage* msg){pEntity->receive(msg);});
		pEntity->send.connect<IMessage*>([this](IMessage* msg){this->receive(msg);});
		
		
	}
	void Scene::Update() {
		
		if( (_clock.now() - _lastUpdate) > _rate ) {
			auto tickTime = _clock.now() - _lastUpdate;
			UpdateMessage updatemsg(tickTime);
			IMessage * message;
			
			for(int i = 0; i<_entities.size(); ++i) {
				_entities[i]->handleMessage(&updatemsg);
				message = _pRenderer->getRenderingMessage();
				_entities[i]->handleMessage(message);
				//delete message;
			
			}

			_lastUpdate = _clock.now();
			
		}
	}
}
#include "stdafx.h"
#include "Scene.h"

namespace LibCommon {
	Scene::Scene(IRenderer* pRenderer) : _pRenderer(pRenderer), _rate(34) {
		
	}
	void Scene::AddEntity(Entity* pEntity) {
		_entities.push_back(std::unique_ptr<Entity>(pEntity));
		
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
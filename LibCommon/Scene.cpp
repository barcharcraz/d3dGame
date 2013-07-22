#include "stdafx.h"
#include "Scene.h"

namespace LibCommon {
	Scene::Scene(IRenderer* pRenderer) : _pRenderer(pRenderer), _rate(34) {
		_lastUpdate = _clock.now();
		
	}
	void Scene::AddEntity(Entity* pEntity) {
		_entities.push_back(std::unique_ptr<Entity>(pEntity));
		pEntity->messenger = &_messenger;
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
				_messenger.send(updatemsg.get());
			}
			_messenger.send(message);
		}
	}
}
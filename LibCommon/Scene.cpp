#include "stdafx.h"
#include "Scene.h"

namespace LibCommon {
	Scene::Scene(IRenderer* pRenderer) : _pRenderer(pRenderer), _rate(34) {
		_lastUpdate = _clock.now();
	}
	void Scene::forwardBubble(Bubbly * msg) {
		_messenger.send(msg);
	}
	void Scene::Update() {
		std::unique_ptr<UpdateMessage> updatemsg;
		if( (_clock.now() - _lastUpdate) > _rate ) {
			auto tickTime = _clock.now() - _lastUpdate;
			updatemsg = make_unique<UpdateMessage>(tickTime);
			_lastUpdate = _clock.now();
			
		}
		if (updatemsg) {
			_messenger.send(updatemsg.get());
		}
		_messenger.send(_pRenderer->getRenderingMessage());
	}
}
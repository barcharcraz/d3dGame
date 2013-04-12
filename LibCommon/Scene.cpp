#include "stdafx.h"
#include "Scene.h"

namespace LibCommon {
	Scene::Scene(IRenderer* pRenderer) : m_pRenderer(pRenderer) {
	}
	void Scene::AddEntity(Entity* pEntity) {
		m_entities.push_back(std::unique_ptr<Entity>(pEntity));
	}
	void Scene::Update() {
		const IMessage * message;
		for(std::unique_ptr<Entity> &e : m_entities) {
			message = m_pRenderer->getRenderingMessage();
			e->handleMessage(*message);
			delete message;
			
		}
	}
}
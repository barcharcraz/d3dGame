#include "stdafx.h"
#include "Scene.h"

namespace LibCommon {
	Scene::Scene(IRenderer* pRenderer) : m_pRenderer(pRenderer) {
	}
	void Scene::AddEntity(Entity* pEntity) {
		m_entities.push_back(std::unique_ptr<Entity>(pEntity));
	}
	void Scene::Update() {

	}
}
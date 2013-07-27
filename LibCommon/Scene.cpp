#include "stdafx.h"
#include "Scene.h"
#include <algorithm>
#include <typeinfo>
#include <set>
namespace LibCommon {
	Scene::Scene(IRenderer* pRenderer) : _pRenderer(pRenderer), _rate(34) {
		_lastUpdate = _clock.now();
	}
	void Scene::Update() {
		using namespace std::chrono;
		auto now = _clock.now();
		_delta = now - _lastUpdate;
		UpdateSystems();
	}
	void Scene::UpdateSystems() {
		for (auto& sys : _systems) {
			auto input = SelectEntities(sys->aspect);
			for (auto ent : input) {
				sys->Process(ent);
			}
		}
	}
	void Scene::AddEntity(Entity* e) {
		_entities.push_back(std::unique_ptr<Entity>(e));
		
	}
	void Scene::AddEntity(std::unique_ptr<Entity> && e) {
		_entities.push_back(std::move(e));
	}
	void Scene::AddSystem(std::unique_ptr<System> && s) {
		_systems.push_back(std::move(s));
	}
	//-------------PRIVATE----------------------
	std::vector<Entity*> Scene::SelectEntities(const std::vector<std::type_index>& info) {
		//^| this function could really use some caching at some point
		std::vector<Entity*> retval;
		for (auto& ent : _entities) {
			if (ent->HasAllComponents(info)) {
				retval.push_back(ent.get());
			}
		}
		return retval;
	}
}
#include "stdafx.h"
#include "Scene.h"
#include <algorithm>
#include <typeinfo>
#include <set>
#include <Utils/exceptions.h>

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
			sys->Init();
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
	void Scene::RemoveEntity(Entity *e) {
		for(_entities::iterator i = _entities.begin(); i != _entities.end(); ++i) {
			if(i->get() == e) {
				sendRemoveMessage(e);
				_entities.erase(i);
				return;
			}
		}
	}

	void Scene::AddSystem(std::unique_ptr<System> && s) {
		_systems.push_back(std::move(s));
		_systems.back()->parent = this;
	}
	void Scene::AddSystem(System* s) {
		_systems.push_back(std::unique_ptr<System>(s));
		_systems.back()->parent = this;
	}
	void Scene::RemoveSystem(System *s) {
		for(_systems::iterator i = _systems.begin(); i != _systems.end(); ++i) {
			if(i->get() == s) {
				_systems.erase(i);
				return;
			}
		}
		throw utils::not_supported_error("could not find element in vector");
	}

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
	Entity* Scene::SelectEntity(const std::vector<std::type_index>& info) {
		for (auto& ent : _entities) {
			if (ent->HasAllComponents(info)) {
				return ent.get();
			}
		}
		return nullptr;
	}
	void Scene::sendRemoveMessage(Entity *e) {
		for(std::unique_ptr<System>& elm : _systems) {
			elm->OnEntityRemove(e);
		}
	}
}

#include "stdafx.h"
#include "Scene.h"
#include <algorithm>
#include <typeinfo>
#include <set>
#include <Utils/exceptions.h>

namespace LibCommon {
	Scene::Scene() : _rate(34) {
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
			sys->PreProcess();
			auto input = SelectEntities(sys->aspect);
			for (auto ent : input) {
				sys->Process(ent);
			}
		}
	}
	void Scene::AddEntity(Entity* e) {
		AddEntity(std::unique_ptr<Entity>(e));
		
	}
	void Scene::AddEntity(std::unique_ptr<Entity> && e) {
		_entities.push_back(std::move(e));
		for (auto& sys : _systems) {
			sys->OnEntityAdd(_entities.back().get());
		}
	}
	void Scene::RemoveEntity(Entity *e) {
		for(auto i = _entities.begin(); i != _entities.end(); i++) {
			if(i->get() == e) {
				sendRemoveMessage(e);
				_entities.erase(i);
				return;
			}
		}
	}

	void Scene::AddSystem(std::unique_ptr<System> && s) {
		auto insertPos = std::find_if(_systems.begin(), _systems.end(), [&](std::unique_ptr<System>& elm) {
			if (s->priority > elm->priority) {
				return true;
			}
			return false;
		});
		auto element = _systems.insert(insertPos, std::move(s));
		element->get()->parent = this;
		(*element)->Init();
	}
	void Scene::AddSystem(System* s) {
		AddSystem(std::unique_ptr<System>(s));
	}
	void Scene::RemoveSystem(System *s) {
		removeSystemEvents(s);
		for(auto i = _systems.begin(); i != _systems.end(); ++i) {
			if(i->get() == s) {
				_systems.erase(i);
				return;
			}
		}
		throw utils::not_supported_error("could not find element in vector");
	}
	void Scene::SetSystemEvents(System* s, const std::set<std::type_index>& types) {
		removeSystemEvents(s);
		for (auto& elm : types) {
			_eventRegistrations.emplace(elm, s);
		}
	}
	void Scene::FireUpdateEvent(Entity* e, Components::IComponent* c) {
		auto range = _eventRegistrations.equal_range(typeid(*c));
		for (auto i = range.first; i != range.second; ++i) {
			if (e->HasAllComponents(i->second->aspect)) {
				i->second->OnEntityUpdate(e, c);
			}
		}
	}
	std::vector<Entity*> Scene::SelectEntities(const std::set<std::type_index>& info) {
		//^| this function could really use some caching at some point
		std::vector<Entity*> retval;
		for (auto& ent : _entities) {
			if (ent->HasAllComponents(info)) {
				retval.push_back(ent.get());
			}
		}
		return retval;
	}
	Entity* Scene::SelectEntity(const std::set<std::type_index>& info) {
		for (auto& ent : _entities) {
			if (ent->HasAllComponents(info)) {
				return ent.get();
			}
		}
		return nullptr;
	}
	std::vector<Components::IComponent*> Scene::SelectComponents(std::type_index type) {
		std::vector<Components::IComponent*> retval;
		for (auto& ent : _entities) {
			if (ent->HasComponent(type)) {
				retval.push_back(ent->Get(type));
			}
		}
		return retval;
	}
	void Scene::sendRemoveMessage(Entity *e) {
		for(std::unique_ptr<System>& elm : _systems) {
			elm->OnEntityRemove(e);
		}
	}
	void Scene::sendAddMessage(Entity* e) {
		for (auto& elm : _systems) {
			elm->OnEntityAdd(e);
		}
	}
	void Scene::removeSystemEvents(System* s) {
		for (auto i = _eventRegistrations.begin(); i != _eventRegistrations.end(); ++i) {
			if (i->second == s) {
				_eventRegistrations.erase(i);
			}
		}
	}
}

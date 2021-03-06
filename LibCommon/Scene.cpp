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
        _systems.finalize_ops();
        _entities.finalize_ops();
        UpdateSystems();
		_lastUpdate = _clock.now();
    }
    void Scene::EraseSystemsNow() {
        _systems.erase(std::remove(begin(_systems), end(_systems), nullptr));
    }
	std::chrono::system_clock::duration Scene::FrameDelta() {
		return _delta;
	}
    void Scene::UpdateSystems() {
        for (auto& sys : _systems) {
            if (sys != nullptr) {
                sys->PreProcess();
                auto input = SelectEntities(sys->aspect);
                for (auto ent : input) {
                    sys->Process(ent);
                }
                sys->PostProcess();
            }
        }
    }
    Entity* Scene::AddEntity(Entity* e) {
        return AddEntity(std::unique_ptr<Entity>(e));
    }
    Entity* Scene::AddEntity(std::unique_ptr<Entity> && e) {
        _entities.push_back(std::move(e));
        sendAddMessage(_entities.back().get());
        return _entities.back().get();
    }
    std::unique_ptr<Entity> Scene::RemoveEntity(Entity *e) {
        std::unique_ptr<Entity> rv = nullptr;
        for(auto i = _entities.begin(); i != _entities.end(); i++) {
            if(i->get() == e) {
                sendRemoveMessage(e);
                rv = std::move(*i);
                _entities.erase(i);
                return rv;
            }
        }
		return rv;
    }

    System* Scene::AddSystem(std::unique_ptr<System> && s) {
        auto insertPos = std::find_if(_systems.begin(), _systems.end(), [&](std::unique_ptr<System>& elm) {
            if (elm != nullptr && s->priority > elm->priority) {
                return true;
            }
            return false;
        });
        auto element = _systems.insert(insertPos, std::move(s))->get();
        element->parent = this;
        element->Init();
        //we want to send add messages for the backlog of entities
        auto backlog = SelectEntities(element->aspect);
        for(auto elm : backlog) {
            element->OnEntityAdd(elm);
        }
        return element;
        
    }
    System* Scene::AddSystem(System* s) {
        return AddSystem(std::unique_ptr<System>(s));
    }
    std::unique_ptr<System> Scene::RemoveSystem(System *s) {
        std::unique_ptr<System> rv = nullptr;
        removeSystemEvents(s);
        for(auto i = _systems.begin(); i != _systems.end(); ++i) {
            if(i->get() == s) {
                rv = std::move(*i);
                _systems.erase(i);
                return rv;
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
            if (ent != nullptr && ent->HasAllComponents(info)) {
                retval.push_back(ent.get());
            }
        }
		for (auto i = _entities.cache_begin(); i != _entities.cache_end(); ++i) {
			if ((*i)->HasAllComponents(info)) {
				retval.push_back(i->get());
			}
		}

        return retval;
    }
    Entity* Scene::SelectEntity(const std::set<std::type_index>& info) {
        for (auto& ent : _entities) {
            if (ent != nullptr && ent->HasAllComponents(info)) {
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
            if (e->HasAllComponents(elm->aspect)) {
                elm->OnEntityRemove(e);
            }
        }
    }
    void Scene::sendAddMessage(Entity* e) {
        for (auto& elm : _systems) {
            if (e->HasAllComponents(elm->aspect)) {
                elm->OnEntityAdd(e);
            }
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

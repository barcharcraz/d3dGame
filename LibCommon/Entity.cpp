#include "stdafx.h"
#include "Entity.h"
#include <algorithm>
#include <Utils/exceptions.h>
namespace LibCommon {
	using namespace Components;
	Entity::Entity() {
		
	}
	Entity::~Entity() {

	}
	void Entity::AddComponent(IComponent* c) {
		using namespace std;
		//typeid(*c) works because type_index has an implicit
		//conversion from type_info
		_components.emplace(typeid(*c), std::unique_ptr<IComponent>(c));
	}
	void Entity::AddComponent(std::unique_ptr<IComponent> && c) {
		using namespace std;
		_components.emplace(typeid(*c.get()), std::move(c));
	}
	void Entity::AddEvent(std::unique_ptr<IComponent> && e) {
		auto iter = _components.emplace(typeid(*e.get()), e);
		_frameComponents.push_back(iter->second.get());
	}
	void Entity::ClearEvents() {
		for (auto e : _frameComponents) {
			RemoveComponent(e);
		}
		_frameComponents.clear();
	}
	std::unique_ptr<IComponent> Entity::RemoveComponent(IComponent* comp) {
		auto rv = RemoveComponentIfExists(typeid(*comp), comp);
		if (rv == nullptr) {
			throw utils::not_found_error("the component was not found in this entity");
		}
		return rv;
	}
	std::unique_ptr<IComponent> Entity::RemoveComponentIfExists(std::type_index type, IComponent* comp) {
		auto range = _components.equal_range(type);
		for (auto i = range.first; i != range.second; ++i) {
			if (i->second.get() == comp) {
				std::unique_ptr<IComponent> rv = std::move(i->second);
				auto msgPos = std::find(_frameComponents.begin(), _frameComponents.end(), comp);
				if (msgPos != _frameComponents.end()) {
					_frameComponents.erase(msgPos);
				}
				_components.erase(i);
				return rv;
			}
		}
		//if we did not find the object we would like to just return a nullptr
		return std::unique_ptr<IComponent>(nullptr);
	}
	bool Entity::HasComponent(std::type_index type) {
		return _components.count(type) > 0;
	}
	bool Entity::HasAllComponents(const std::set<std::type_index>& types) {
		bool retval = true;
		for (auto& type : types) {
			if (_components.count(type) == 0) {
				retval = false;
			}
		}
		
		return retval;
	}
	
}

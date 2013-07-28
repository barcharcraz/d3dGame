#include "stdafx.h"
#include "Entity.h"
#include <algorithm>
namespace LibCommon {
	using namespace Components;
	Entity::Entity() {
		
	}
	void Entity::AddComponent(IComponent* c) {
		using namespace std;
		if (_components.count(type_index(typeid(*c))) != 0) {
			throw std::runtime_error("ERROR: entities may not have more than one component of the same type");
		}
		//typeid(*c) works because type_index has an implicit
		//conversion from type_info
		_components[typeid(*c)] = std::unique_ptr<IComponent>(c);
	}
	void Entity::AddComponent(std::unique_ptr<IComponent> && c) {
		using namespace std;
		if (_components.count(type_index(typeid(c))) != 0) {
			throw std::runtime_error("ERROR: entities may not have more than one component of the same type");
		}
		_components[typeid(c)] = std::move(c);
	}
	bool Entity::HasComponent(std::type_index type) {
		return _components.count(type) > 0;
	}
	bool Entity::HasAllComponents(const std::vector<std::type_index>& types) {
		bool retval = true;
		for (auto& type : types) {
			if (_components.count(type) == 0) {
				retval = false;
			}
		}
		return retval;
	}
	
}

#include "stdafx.h"
#include "Entity.h"
#include <algorithm>
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

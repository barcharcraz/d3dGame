#ifndef LIBCOMMON_ENTITY_H
#define LIBCOMMON_ENTITY_H
#include <LibComponents/IComponent.h>
#include <set>
#include <map>
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <functional>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "Get.hpp"
#include "IMessage.h"
#include "Bubbly.h"
#include <Utils/make_unique.h>
namespace LibCommon {
	class Entity {
	public:
		Entity();
		virtual ~Entity();
		void AddComponent(Components::IComponent* c);
		void AddComponent(std::unique_ptr<Components::IComponent> && c);
		template<typename T, typename... Args>
		void AddComponent(Args&&... args) {
			if (_components.count(typeid(T)) != 0) {
				throw std::runtime_error("ERROR: Entites may not have more than one component of a given type");
			}
            
			_components[typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
		}
		template<typename T>
		T* Get() {
			auto range = _components.equal_range(typeid(T));
			return static_cast<T*>((*range.first).second.get());
		}
		template<typename T>
		T* GetOptional() {
			if (_components.count(typeid(T))) {
				return Get<T>();
			} else {
				return nullptr;
			}
		}
		Components::IComponent* Get(std::type_index type) {
			auto range = _components.equal_range(type);
			return range.second->second.get();
		}
		template<typename T>
		std::vector<T*> GetAll() {
			auto range = _components.equal_range(typeid(T));
			std::vector<T*> retval;
			for (auto i = range.first; i != range.second; i++) {
				retval.push_back(i->second.get());
			}
			return retval;
		}
		bool HasComponent(std::type_index type);
		bool HasAllComponents(const std::set<std::type_index>& types);
	private:
		std::multimap<std::type_index, std::unique_ptr<Components::IComponent> > _components;
		
	};
}
#endif

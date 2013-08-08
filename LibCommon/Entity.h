#ifndef LIBCOMMON_ENTITY_H
#define LIBCOMMON_ENTITY_H
#include <LibComponents/IComponent.h>
#include <vector>
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
			return static_cast<T*>(_components.at(typeid(T)).get());
		}
		template<typename T>
		T* GetOptional() {
			if (_components.count(typeid(T))) {
				return static_cast<T*>(_components.at(typeid(T)).get());
			} else {
				return nullptr;
			}
		}
		
		bool HasComponent(std::type_index type);
		bool HasAllComponents(const std::vector<std::type_index>& types);
	private:
		std::map<std::type_index, std::unique_ptr<Components::IComponent> > _components;
		
	};
}
#endif

#ifndef LIBCOMMON_ENTITY_H
#define LIBCOMMON_ENTITY_H
#include <LibComponents/IComponent.h>
#include <vector>
#include <map>
#include <memory>
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
		void AddComponent(Components::IComponent* c);
		void AddComponent(std::unique_ptr<Components::IComponent> && c);
		template<typename T>
		T* Get() {
			return static_cast<T*>(_components.at(typeid(T)).get());
		}
		bool HasComponent(std::type_index type);
		bool HasAllComponents(const std::vector<std::type_index>& types);
	private:
		std::map<std::type_index, std::unique_ptr<Components::IComponent> > _components;
		
	};
}
#endif

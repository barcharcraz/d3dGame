#ifndef LIBCOMMON_ENTITY_H
#define LIBCOMMON_ENTITY_H
#include "IComponent.h"
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
		void AddComponent(IComponent* c);
		void AddComponent(std::unique_ptr<IComponent> && c);

		bool HasComponent(std::type_index type);
		bool HasAllComponents(const std::vector<std::type_index>& types);
	private:
		std::map<std::type_index, std::unique_ptr<IComponent> > _components;
		
	};
}
#endif

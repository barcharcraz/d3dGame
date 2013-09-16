#ifndef LIBCOMMON_SYSTEM_H
#define LIBCOMMON_SYSTEM_H
#include <set>
#include <tuple>
#include <typeindex>
#include "Entity.h"
namespace Components {
	class IComponent;
}
namespace LibCommon {
	class Scene;
	enum class Priority {
		HIGH,
		MEDIUM,
		LOW
	};
	class System {
	public:
		Scene* parent;
		std::set<std::type_index> aspect;
		System(const std::set<std::type_index>& types);
		System();
		System(const std::set<std::type_index>& types, Priority prio);
		System(Priority prio);
		void EnableUpdate();
		void EnableUpdate(const std::set<std::type_index>& types);
		void SetUpdateFilter(const std::set<std::type_index>& types);
		void NotifyUpdate(Entity*, Components::IComponent*);
		virtual void OnEntityAdd(Entity*) {}
		virtual void Init(){}
        virtual void PreProcess() {}
		virtual void Process(Entity*) {}
		virtual void OnEntityRemove(Entity*) {}
		virtual void OnEntityUpdate(Entity*, Components::IComponent*) {}
		virtual ~System() = 0;
		Priority priority;
	};
    inline System::~System() {}


}
#endif

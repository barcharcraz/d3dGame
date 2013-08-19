#ifndef LIBCOMMON_SYSTEM_H
#define LIBCOMMON_SYSTEM_H
#include <set>
#include <tuple>
#include <typeindex>
#include "Entity.h"
#include "Scene.h"
namespace LibCommon {
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
        virtual void Init() {}
		virtual void Process(Entity* ent) = 0;
		virtual void OnEntityRemove(Entity* ent) {}
		virtual ~System() = 0;
		Priority priority;
	};
    inline System::~System() {}


}
#endif

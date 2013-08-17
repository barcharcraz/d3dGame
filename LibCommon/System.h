#ifndef LIBCOMMON_SYSTEM_H
#define LIBCOMMON_SYSTEM_H
#include <vector>
#include <tuple>
#include <typeindex>
#include "Entity.h"
namespace LibCommon {
    class Scene;
	class System {
	public:
		Scene* parent;
		std::vector<std::type_index> aspect;
		System(std::vector<std::type_index> types);
		System();
        virtual void Init() {}
		virtual void Process(Entity* ent) = 0;
		virtual void OnEntityRemove(Entity* ent) {}
		virtual ~System() = 0;
	};
    inline System::~System() {}


}
#endif

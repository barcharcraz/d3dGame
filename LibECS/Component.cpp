#include "Component.h"
#include <typeindex>
#include <map>
namespace sparse {
    namespace ecs {
        namespace {
            ComponentType nextID = 0;
            std::map<std::type_index, ComponentType> typeMap;
        }
        ComponentType GenID() {
            ComponentType rv = nextID;
            nextID += 1;
            return rv;
        }
		ComponentType GenID(std::type_index info) {
			if (typeMap.count(info) > 0) {
				return typeMap[info];
			} else {
				typeMap[info] = GenID();
			}
		}
    }
}
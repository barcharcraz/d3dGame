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
        ComponentType QueryType(std::type_info type) {

        }
    }
}
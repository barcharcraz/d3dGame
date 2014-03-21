#ifndef SPARSE_ECS_COMPONENT_H
#define SPARSE_ECS_COMPONENT_H
#include <typeinfo>
namespace sparse {
    namespace ecs {
        typedef int ComponentType;
        typedef int Entity;
        ComponentType GenID();
        struct Component {
            ComponentType type;
            std::size_t size;
            Entity ent;
        };
    }
}

#endif
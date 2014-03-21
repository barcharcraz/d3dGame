#ifndef SPARSE_ECS_SYSTEM_H
#define SPARSE_ECS_SYSTEM_H
#include <vector>
#include "Component.h"
namespace sparse {
    namespace ecs {
        class Scene;
        class Row;
        typedef void(*SystemFunc)(const Scene*const, Row*const);
        struct System {
            ComponentType write_comp;
            SystemFunc func;
        };
    }
}

#endif
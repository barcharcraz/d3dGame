#ifndef SPARSE_ECS_SYSTEM_H
#define SPARSE_ECS_SYSTEM_H
#include <vector>
#include "Component.h"
namespace sparse {
    namespace ecs {
        class Scene;
        class Row;
        typedef void(*SystemFunc)(Row*, const Scene*, Row*);
        struct System {
			//the write component is the one
			//shared component that a particular
			//system is allowed to write to.
			//If more than one system write to
			//the same component the result
			//is undefined
            ComponentType write_comp;
			//the state component is writeable
			//by this component. It is UNDEFINED
			//BEHAVIOR if ANY other system EVER
			//reads or writes to it
			ComponentType state_comp;
            SystemFunc update_func;
        };
    }
}

#endif
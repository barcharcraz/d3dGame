#include "World.h"
namespace sparse {
    namespace ecs {
        void World::AddSystem(SystemFunc func, ComponentType writeComp) {
            systems.push_back(System{ writeComp, func });
        }
        void World::AddSystem(const System& sys) {
            systems.push_back(sys);
        }
        void World::Update() {
            for (auto fun : systems) {
                fun.update_func(
					compState.GetRow(fun.state_comp),
					&current, 
					next.GetRow(fun.write_comp));
            }
            current = next;
        }
    }
}
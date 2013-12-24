#ifndef SPARSE_ECS_WORLD
#define SPARSE_ECS_WORLD
#include "Scene.h"
#include "System.h"
#include <vector>
namespace sparse {
    namespace ecs {
        class World {
        public:
            void AddSystem(SystemFunc func, ComponentType writeComp);
            void AddSystem(const System& sys);
            void Update();
        private:
            std::vector<System> systems;
            Scene current;
            Scene next;
			Scene compState;
        };
    }
}

#endif
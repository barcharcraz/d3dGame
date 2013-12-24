#ifndef SPARSE_ECS_SCENE_H
#define SPARSE_ECS_SCENE_H
#include "Component.h"
#include "Row.h"
#include <vector>
#include <memory>
namespace sparse {
    namespace ecs {
        class Scene {
        public:
            //! \brief adds comp to the scene
            //! this is the low level unsafe version
            //! of add component. Returns a pointer to
            //! the newly added component.
            //!
            //! Preconditions: void* must be a trivial layout
            //! type that can be cast to a component*. Thus
            //! it must consist of a ComponentID followed by a
            //! size_t followed by a Entity
            void* AddComponent(void* comp);

            Row* GetRow(ComponentType type);
			const Row* GetRow(ComponentType type) const;
        private:
            std::vector<Row> data;
        };
    }
}

#endif
#include "Scene.h"
namespace sparse {
    namespace ecs {
        Row*const Scene::GetRow(ComponentType type) {
            return &data.at(type);
        }
        void* Scene::AddComponent(void* value) {
            Component* comp = reinterpret_cast<Component*>(value);
            if (data.size() <= comp->type) {
                data.resize(comp->type);
            }
            data[comp->type].push_back(value);
            return data[comp->type].back();
        }
    }
}
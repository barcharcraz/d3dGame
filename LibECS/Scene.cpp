#include "Scene.h"
namespace sparse {
    namespace ecs {
        Row*const Scene::GetRow(ComponentType type) {
            return &data.at(type);
        }
        void* Scene::AddComponent(void* value) {
            Component* comp = reinterpret_cast<Component*>(value);
            if (data.size() <= static_cast<std::size_t>(comp->info->type)) {
                data.resize(comp->info->type);
            }
            data[comp->info->type].push_back(value);
            return data[comp->info->type].back();
        }
    }
}

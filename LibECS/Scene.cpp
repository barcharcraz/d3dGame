#include "Scene.h"
namespace sparse {
    namespace ecs {
        Row* Scene::GetRow(ComponentType type) {
			if (type == -1) {
				return nullptr;
			}
            return &data.at(type);
        }
		const Row* Scene::GetRow(ComponentType type) const {
			if (type == -1) {
				return nullptr;
			}
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

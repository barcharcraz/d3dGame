#ifndef LIBCOMMON_SCENE_H
#define LIBCOMMON_SCENE_H
#include "IRenderer.h"
#include "Entity.h"
#include "IMessage.h"
#include "Bubbly.h"
#include "UpdateMessage.h"
#include "System.h"
#include <memory>
#include <vector>
#include <chrono>
#include <functional>
namespace LibCommon {
	class Scene {
	public:
		Scene();
		void Update();
		void AddEntity(Entity* e);
		void AddEntity(std::unique_ptr<Entity> && e);
		template<typename T, typename... Args>
		void AddEntity(Args && ... args) {
			AddEntity(std::make_unique<T>(std::forward<Args>(args)...));
		}
		void RemoveEntity(Entity* e);
		void AddSystem(std::unique_ptr<System> && s);
		void AddSystem(System * s);
		
		void RemoveSystem(System* s);

		std::vector<Components::IComponent*> SelectComponents(std::type_index type);
		template<typename T>
		std::vector<T*> SelectComponents() {
			std::vector<T*> retval;
			for (auto& ent : _entities) {
				if (ent->HasComponent(typeid(T))) {
					retval.push_back(ent->Get<T>());
				}
			}
			return retval;
		}
		std::vector<Entity*> SelectEntities(const std::set<std::type_index>& types);
		//! \brief SelectEntities job is to select entities that have the components
		//! specified in the types parameter, depending on how entities are stored
		//! this may involve a database query
		Entity* SelectEntity(const std::set<std::type_index>& types);
	protected:
	private:
		std::vector<std::unique_ptr<System>> _systems;
		std::vector<std::unique_ptr<Entity>> _entities;
		//! \brief sends a removal message to all systems for the
		//! entity e
		void sendRemoveMessage(Entity* e);
		void sendAddMessage(Entity* e);
		void UpdateSystems();
		
		std::chrono::system_clock _clock;
		std::chrono::system_clock::duration _delta;
		std::chrono::system_clock::time_point _lastUpdate;
		std::chrono::milliseconds _rate;
	};
}
#endif

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
namespace LibCommon {
	class Scene {
	public:
		Scene(IRenderer* pRenderer);
		void Update();
		void AddEntity(Entity* e);
		void AddEntity(std::unique_ptr<Entity> && e);
		void AddSystem(std::unique_ptr<System> && s);

		std::vector<Entity*> SelectEntities(const std::vector<std::type_index>& types);
		Entity* SelectEntity(const std::vector<std::type_index>& types);
	protected:
	private:
		std::vector<std::unique_ptr<System>> _systems;
		std::vector<std::unique_ptr<Entity>> _entities;

		//! \brief SelectEntities job is to select entities that have the components
		//! specified in the types parameter, depending on how entities are stored
		//! this may involve a database query
		
		void UpdateSystems();
		std::unique_ptr<IRenderer> _pRenderer;
		std::chrono::system_clock _clock;
		std::chrono::system_clock::duration _delta;
		std::chrono::system_clock::time_point _lastUpdate;
		std::chrono::milliseconds _rate;
	};
}
#endif
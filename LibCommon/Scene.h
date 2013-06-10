#ifndef LIBCOMMON_SCENE_H
#define LIBCOMMON_SCENE_H
#include "IRenderer.h"
#include "Entity.h"
#include "IMessage.h"
#include "IComponent.h"
#include "UpdateMessage.h"
#include <memory>
#include <vector>
#include <chrono>
namespace LibCommon {
	class Scene : IComponent {
	public:
		Scene(IRenderer* pRenderer);
		void Update();
		void AddEntity(Entity* pEntity);
	private:
		std::unique_ptr<IRenderer> _pRenderer;
		std::vector<std::shared_ptr<Entity> > _entities;
		std::chrono::system_clock _clock;
		std::chrono::system_clock::time_point _lastUpdate;
		std::chrono::milliseconds _rate;
	};
}
#endif
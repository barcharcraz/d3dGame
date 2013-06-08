#ifndef LIBCOMMON_SCENE_H
#define LIBCOMMON_SCENE_H
#include "IRenderer.h"
#include "Entity.h"
#include <memory>
#include <vector>
#include <chrono>
namespace LibCommon {
	class Scene {
	public:
		Scene(IRenderer* pRenderer);
		void Update();
		void AddEntity(Entity* pEntity);
	private:
		std::unique_ptr<IRenderer> m_pRenderer;
		std::vector<std::shared_ptr<Entity> > m_entities;
		chrono::system_clock _mClock;
		chrono::system_clock::time_point _mLastUpdate;
		chrono::duration<float, std::ratio<30, 1000> > _mRate;
	};
}
#endif
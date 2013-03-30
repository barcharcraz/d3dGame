#ifndef LIBCOMMON_SCENE_H
#define LIBCOMMON_SCENE_H
#include "IRenderer.h"
#include "Entity.h"
#include <memory>
#include <vector>
namespace LibCommon {
	class Scene {
	public:
		Scene(IRenderer* pRenderer);
		void Update();
		void AddEntity(Entity* pEntity);
	private:
		std::unique_ptr<IRenderer> m_pRenderer;
		std::vector<std::unique_ptr<Entity> > m_entities;
	};
}
#endif
#ifndef LIBSYSTEMS_COLLISIONSYSTEM_H
#define LIBSYSTEMS_COLLISIONSYSTEM_H
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
namespace Systems {
	class CollisionSystem : public LibCommon::System {
	public:
		CollisionSystem();
		virtual void Init() override;
		virtual void OnEntityAdd(LibCommon::Entity* ent) override;
		virtual void OnEntityRemove(LibCommon::Entity* ent) override;
		virtual void Process(LibCommon::Entity* ent) override;
	private:
		std::vector<LibCommon::Entity*> entCache;
	};
}

#endif
#ifndef LIBSYSTEMS_COLLISIONDETECTIONSYSTEM_H
#define LIBSYSTEMS_COLLISIONDETECTIONSYSTEM_H
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
#include <LibPhysics/SweepAndPrune.h>
namespace Systems {
	class CollisionDetectionSystem : public LibCommon::System {
	public:
		CollisionDetectionSystem();
		virtual void Init() override;
		virtual void OnEntityAdd(LibCommon::Entity* ent) override;
		virtual void OnEntityUpdate(LibCommon::Entity* ent, Components::IComponent* comp) override;
		virtual void OnEntityRemove(LibCommon::Entity* ent) override;
	private:
		Physics::SweepAndPrune sap;
	};
}

#endif
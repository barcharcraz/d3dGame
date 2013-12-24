#ifndef LIBSYSTEMS_COLLISIONDETECTIONSYSTEM_H
#define LIBSYSTEMS_COLLISIONDETECTIONSYSTEM_H
#include <ecs.h>
#include <LibPhysics/SweepAndPrune.h>
namespace Systems {
	class CollisionDetectionSystem : public sparse::ecs::System {
	public:
		CollisionDetectionSystem();
		static void CollisionUpdate(sparse::ecs::Row*,
			const sparse::ecs::Scene*,
			sparse::ecs::Row*);
		virtual void Init() override;
		virtual void OnEntityAdd(LibCommon::Entity* ent) override;
		virtual void OnEntityUpdate(LibCommon::Entity* ent, Components::IComponent* comp) override;
		virtual void OnEntityRemove(LibCommon::Entity* ent) override;
	private:
		struct state : public sparse::ecs::ComponentHelper<state> {
			Physics::SweepAndPrune sap;
		};
	};
}

#endif
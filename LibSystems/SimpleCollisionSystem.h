#ifndef LIBSYSTEMS_SIMPLECOLLISIONSYSTEM_H
#define LIBSYSTEMS_SIMPLECOLLISIONSYSTEM_H
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
namespace Systems {
	class SimpleCollisionSystem : public LibCommon::System {
	public:
		SimpleCollisionSystem();
		virtual void Init() override;
		virtual void OnEntityUpdate(LibCommon::Entity* ent, Components::IComponent* comp);
		virtual void Process(LibCommon::Entity* ent);
	};
}

#endif
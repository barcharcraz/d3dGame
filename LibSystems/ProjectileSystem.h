#ifndef LIBSYSTEMS_PROJECTILESYSTEM_H
#define LIBSYSTEMS_PROJECTILESYSTEM_H
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
#include <LibComponents/IComponent.h>
namespace Systems {
	class ProjectileSystem : public LibCommon::System {
	public:
		ProjectileSystem();
		virtual void Init() override;
		virtual void OnEntityUpdate(LibCommon::Entity* ent, Components::IComponent* comp);
		virtual void Process(LibCommon::Entity* ent) override;
	};
}


#endif
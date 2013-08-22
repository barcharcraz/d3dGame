#ifndef LIBSYSTEMS_SIMPLECOLLISIONSYSTEM_H
#define LIBSYSTEMS_SIMPLECOLLISIONSYSTEM_H
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
namespace Systems {
	class SimpleCollisionSystem : public LibCommon::System {
	public:
		SimpleCollisionSystem();
		virtual void Process(LibCommon::Entity* ent);
	};
}

#endif
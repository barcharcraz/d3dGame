#ifndef LIBCOMMON_VELOCITYSYSTEM3D_H
#define LIBCOMMON_VELOCITYSYSTEM3D_H
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
namespace Systems {
	class VelocitySystem3D : public LibCommon::System {
	public:
		VelocitySystem3D();
		virtual void Process(LibCommon::Entity* e) override;
	};
}

#endif
#ifndef LIBCOMMON_VELOCITYSYSTEM3D_H
#define LIBCOMMON_VELOCITYSYSTEM3D_H
#include "System.h"
#include "Entity.h"
namespace LibCommon {
	class VelocitySystem3D : public System {
		VelocitySystem3D();
		virtual void Process(Entity* e) override;
	};
}

#endif
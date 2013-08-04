#ifndef LIBSYSTEMS_MOVEMENTCONTROLLER3D_H
#define LIBSYSTEMS_MOVEMENTCONTROLLER3D_H
#include "stdafx.h"
#include <LibCommon/System.h>
namespace Systems {
	class MovementController3D : public LibCommon::System {
	public:
		MovementController3D();
		virtual void Process(LibCommon::Entity * e) override;
	};
}

#endif
#ifndef LIBSYSTEMS_GUNCONTROLLER_H
#define LIBSYSTEMS_GUNCONTROLLER_H
#include "stdafx.h"
#include <LibCommon/System.h>
namespace Systems {
	class GunController : public LibCommon::System {
	public:
		GunController();
		virtual void Process(LibCommon::Entity* e) override;
	};
}

#endif
#ifndef LIBCOMMON_VELOCITY2D_H
#define LIBCOMMON_VELOCITY2D_H
#include "stdafx.h"
#include "IComponent.h"
#include "Get.hpp"
#include "Transform.hpp"
#include "UpdateMessage.h"
namespace LibCommon {
	class Velocity2D : public IComponent {
	public:
		Velocity2D();
		Velocity2D(Eigen::Vector2f vel);
		Eigen::Vector2f velocity;
	private:
		void init();
		void HandleUpdate(UpdateMessage * msg);
		void HandleGetVelocity(Get<Eigen::Vector2f> * msg);
	};
}

#endif
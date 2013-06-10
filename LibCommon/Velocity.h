#ifndef LIBCOMMON_VELOCITY_H
#define LIBCOMMON_VELOCITY_H
#include "stdafx.h"
#include "IComponent.h"
#include "Get.hpp"
#include "Transform2D.h"
#include "UpdateMessage.h"
namespace LibCommon {
	class Velocity : public IComponent {
	public:
		Velocity();
		Velocity(Eigen::Vector2f vel);
		Eigen::Vector2f velocity;
	private:
		void init();
		void HandleUpdate(UpdateMessage * msg);
		void HandleGetVelocity(Get<Velocity, Eigen::Vector2f> * msg);
	};
}

#endif
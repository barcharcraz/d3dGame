#ifndef LIBCOMMON_VELOCITY_H
#define LIBCOMMON_VELOCITY_H
#include "stdafx.h"
#include "IComponent.h"
#include "UpdateMessage.h"
namespace LibCommon {
	class Velocity : public IComponent {
	public:
		Velocity();
		Velocity(Eigen::Vector2f vel);
		Eigen::Vector2f velocity;
	private:
		void HandleUpdate(UpdateMessage * msg);
	};
}

#endif
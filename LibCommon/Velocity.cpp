#include "stdafx.h"
#include "Velocity.h"
namespace LibCommon {
	Velocity::Velocity() 
		: velocity(Eigen::Vector2f::Identity()) 
	{
		init();
	}

	Velocity::Velocity(Eigen::Vector2f vel)
		: velocity(vel)
	{
		init();
	}

	void Velocity::init() {
		BIND(HandleUpdate, UpdateMessage);
	}

	void Velocity::HandleUpdate(UpdateMessage * msg) {
		//TODO: implement this
	}
}
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
		BIND(HandleGetVelocity, Get<Velocity COM Eigen::Vector2f>);
	}

	void Velocity::HandleUpdate(UpdateMessage * msg) {
		std::chrono::milliseconds ticktime = std::chrono::duration_cast<std::chrono::milliseconds>(msg->tick);
		Eigen::Vector2f normv(velocity.x() * ticktime.count(), velocity.y() * ticktime.count());
		Get<Transform2D, Eigen::Affine2f> transform(this);
		send(&transform);
		transform.value->translate(normv);

	}
	void Velocity::HandleGetVelocity(Get<Velocity, Eigen::Vector2f> * msg) {
		msg->value = &this->velocity;
	}
}
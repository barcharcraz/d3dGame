#include "stdafx.h"
#include "Velocity2D.h"
namespace LibCommon {
	Velocity2D::Velocity2D() 
		: velocity(Eigen::Vector2f::Identity()) 
	{
		init();
	}

	Velocity2D::Velocity2D(Eigen::Vector2f vel)
		: velocity(vel)
	{
		init();
	}

	void Velocity2D::init() {
		receive.connect<UpdateMessage*>([this](UpdateMessage* msg){this->HandleUpdate(msg);});
		receive.connect<Get<Velocity2D, Eigen::Vector2f>* >([this](Get<Velocity2D, Eigen::Vector2f>* msg){this->HandleGetVelocity(msg);});
	}

	void Velocity2D::HandleUpdate(UpdateMessage * msg) {
		std::chrono::milliseconds ticktime = std::chrono::duration_cast<std::chrono::milliseconds>(msg->tick);
		Eigen::Vector2f normv(velocity.x() * ticktime.count(), velocity.y() * ticktime.count());
		Get<Transform2D, Eigen::Affine2f> transform(this);
		send(&transform);
		transform.value->translate(normv);

	}
	void Velocity2D::HandleGetVelocity(Get<Velocity2D, Eigen::Vector2f> * msg) {
		msg->value = &this->velocity;
	}
}
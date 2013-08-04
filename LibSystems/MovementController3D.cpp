#include "stdafx.h"
#include "MovementController3D.h"
#include <LibComponents/Velocity.h>
#include <LibInput/Input.h>
namespace Systems {
	MovementController3D::MovementController3D()
		: System({ typeid(Components::Velocity3D), typeid(Input::Input) })
	{

	}
	void MovementController3D::Process(LibCommon::Entity * e) {
		using namespace Components;
		namespace In = Input;
		using namespace Eigen;
		auto vel = e->Get<Velocity3D>();
		auto inp = e->Get<In::Input>();
		Vector3f newVel = Vector3f::Zero();
		
		if (inp->ActionStatus("Left")) {
			newVel += Vector3f::UnitX();
		}
		if (inp->ActionStatus("Right")) {
			newVel -= Vector3f::UnitX();
		}
		if (inp->ActionStatus("Forward")) {
			newVel += Vector3f::UnitZ();
		}
		if (inp->ActionStatus("Backward")) {
			newVel -= Vector3f::UnitZ();
		}
		
		vel->velocity.translation() = newVel;

	}
}
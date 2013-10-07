#include "stdafx.h"
#include <Eigen/Eigen>
#include "MovementController3D.h"
#include <LibComponents/Velocity.h>
#include <Utils/math.h>
#include <LibInput/Input.h>
#include <LibComponents/Transform.h>
namespace Systems {
	MovementController3D::MovementController3D()
		: System({ typeid(Components::Velocity3D), typeid(Input::Input), typeid(Components::Transform3D) })
	{
		priority = LibCommon::Priority::HIGH;
	}
	void MovementController3D::Process(LibCommon::Entity * e) {
		using namespace Components;
		namespace In = Input;
		using namespace Eigen;
		auto vel = e->Get<Velocity3D>();
		auto inp = e->Get<In::Input>();
		//auto trans = e->Get<Components::Transform3D>();
		Affine3f newVel( Affine3f::Identity() );
		auto rotY = inp->AxisAction("Horizontal");
		auto rotX = inp->AxisAction("Vertical");
		float speed = 0.025f;
		
		if (inp->Action("Left")) {
			newVel.translate(Eigen::Vector3f::UnitX() * speed);
		}
		if (inp->Action("Right")) {
			newVel.translate(-Eigen::Vector3f::UnitX() * speed);
		}
		if (inp->Action("Forward")) {
			newVel.translate(Eigen::Vector3f::UnitZ() * speed);
		}
		if (inp->Action("Backward")) {
			newVel.translate(-Eigen::Vector3f::UnitZ() * speed);
		}
		//Eigen::Vector3f transUp = trans->transform.rotation() * Eigen::Vector3f::UnitY();
		
		newVel.rotate(AngleAxisf(rotX, -Vector3f::UnitX()));
		newVel.rotate(AngleAxisf(rotY, -Vector3f::UnitY()));
		
		
		vel->velocity = std::move(newVel);

	}
}
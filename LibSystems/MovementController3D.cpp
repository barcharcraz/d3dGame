#include "stdafx.h"
#include "MovementController3D.h"
#include <LibComponents/Velocity.h>
#include <LibInput/Input.h>
#include <LibComponents/Transform.h>
namespace Systems {
	MovementController3D::MovementController3D()
		: System({ typeid(Components::Velocity3D), typeid(Input::Input), typeid(Components::Transform3D) })
	{

	}
	void MovementController3D::Process(LibCommon::Entity * e) {
		using namespace Components;
		namespace In = Input;
		using namespace Eigen;
		auto vel = e->Get<Velocity3D>();
		auto inp = e->Get<In::Input>();
		auto trans = e->Get<Components::Transform3D>();
		Affine3f newVel( Affine3f::Identity() );
		auto rotY = inp->AxisAction("Horizontal");
		auto rotX = inp->AxisAction("Vertical");
		
		if (inp->Action("Left")) {
			newVel.pretranslate(Vector3f::UnitX());
		}
		if (inp->Action("Right")) {
			newVel.pretranslate(-Vector3f::UnitX());
		}
		if (inp->Action("Forward")) {
			newVel.pretranslate(Vector3f::UnitZ());
		}
		if (inp->Action("Backward")) {
			newVel.pretranslate(-Vector3f::UnitZ());
		}
		Eigen::Vector3f transUp = trans->transform.rotation() * Eigen::Vector3f::UnitY();
		
		newVel *= AngleAxisf(rotX, Vector3f::UnitX());
		newVel *= AngleAxisf(rotY, transUp);
		
		
		vel->velocity = std::move(newVel);

	}
}
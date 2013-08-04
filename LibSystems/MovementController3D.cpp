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
		Affine3f newVel( Affine3f::Identity() );
		auto rotY = inp->AxisAction("Horizontal");
		auto rotX = inp->AxisAction("Vertical");
		newVel.rotate( AngleAxisf(rotY, Vector3f::UnitY()) );
		newVel.rotate( AngleAxisf(rotX, Vector3f::UnitX()) );
		if (inp->Action("Left")) {
			newVel *= Translation3f(Vector3f::UnitX());
		}
		if (inp->Action("Right")) {
			newVel *= Translation3f(-Vector3f::UnitX());
		}
		if (inp->Action("Forward")) {
			newVel *= Translation3f(Vector3f::UnitZ());
		}
		if (inp->Action("Backward")) {
			newVel *= Translation3f(-Vector3f::UnitZ());
		}
		
		vel->velocity = std::move(newVel);

	}
}
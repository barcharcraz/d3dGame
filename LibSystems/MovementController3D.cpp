#include "stdafx.h"
#include <Eigen/Eigen>
#include "MovementController3D.h"
#include <LibComponents/Velocity.h>
#include <Utils/math.h>
#include <LibInput/Input.h>
#include <LibComponents/Transform.h>
namespace Systems {
    MovementController3D::MovementController3D()
        : System({ typeid(Components::PremulVelocity3D), typeid(Input::Input), typeid(Components::Transform3D) })
    {
        priority = LibCommon::Priority::HIGH;
    }
    void MovementController3D::Process(LibCommon::Entity * e) {
        using namespace Components;
        namespace In = Input;
        using namespace Eigen;
        auto vel = e->Get<PremulVelocity3D>();
        auto inp = e->Get<In::Input>();
        auto trans = e->Get<Components::Transform3D>();
		Vector3f newLinear = Vector3f::Zero();
		Quaternionf newRot = Quaternionf::Identity();
        auto rotY = -inp->AxisAction("Horizontal");
        auto rotX = -inp->AxisAction("Vertical");
        float speed = 0.025f;
        
        if (inp->Action("Left")) {
            newLinear += (-Eigen::Vector3f::UnitX() * speed);
        }
        if (inp->Action("Right")) {
            newLinear += (Eigen::Vector3f::UnitX() * speed);
        }
        if (inp->Action("Forward")) {
            newLinear += (-Eigen::Vector3f::UnitZ() * speed);
        }
        if (inp->Action("Backward")) {
            newLinear += (Eigen::Vector3f::UnitZ() * speed);
        }
        //Eigen::Vector3f transUp = trans->transform.rotation() * Eigen::Vector3f::UnitY();
        newRot *= Quaternionf(AngleAxisf(static_cast<float>(rotX), -Vector3f::UnitX()));
        newRot *= Quaternionf(AngleAxisf(static_cast<float>(rotY), -Vector3f::UnitY()));
		newLinear = trans->rotation.inverse() * newLinear;
        
		vel->linear = newLinear;
		vel->angular = newRot;

    }
}

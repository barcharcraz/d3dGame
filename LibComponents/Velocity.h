#ifndef LIBCOMPONENTS_VELOCITY_H
#define LIBCOMPONENTS_VELOCITY_H
#include <Eigen/Geometry>
#include "IComponent.h"
namespace Components {
    struct Velocity2D : public IComponent {
        Velocity2D(const Eigen::Affine2f& vel) : velocity(vel) {}
        Eigen::Affine2f velocity;
    };
    struct Velocity3D : public IComponent {
		Velocity3D(const Eigen::Affine3f& vel);
		Velocity3D(const Eigen::Vector3f& lin, const Eigen::Quaternionf& rot);
		Velocity3D(const Eigen::Vector3f& lin);
		Velocity3D(const Eigen::Quaternionf& ang);
		Eigen::Vector3f linear;
		Eigen::Quaternionf angular;
    };
    struct PremulVelocity3D : public IComponent {
		PremulVelocity3D(const Eigen::Affine3f& vel);
		PremulVelocity3D(const Eigen::Vector3f& lin, const Eigen::Quaternionf& rot);
		PremulVelocity3D(const Eigen::Vector3f& lin);
		PremulVelocity3D(const Eigen::Quaternionf& rot);
		Eigen::Vector3f linear;
		Eigen::Quaternionf angular;

    };
}
#endif
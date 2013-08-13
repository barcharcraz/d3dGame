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
		Velocity3D(const Eigen::Affine3f& vel) : velocity(vel) {}
		Eigen::Affine3f velocity;
	};
}
#endif
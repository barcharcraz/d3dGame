#ifndef LIBCOMPONENTS_VELOCITY_H
#define LIBCOMPONENTS_VELOCITY_H
#include <Eigen/Geometry>
#include "IComponent.h"
namespace Components {
	struct Velocity2D : public IComponent {
		Eigen::Affine2f velocity;
	};
	struct Velocity3D : public IComponent {
		Eigen::Affine3f velocity;
	};
}
#endif
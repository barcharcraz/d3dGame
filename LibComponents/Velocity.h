#ifndef LIBCOMPONENTS_VELOCITY_H
#define LIBCOMPONENTS_VELOCITY_H
#include <Eigen/Geometry>
#include <ecs.h>
namespace Components {
    struct Velocity2D : public sparse::ecs::Component {
		static sparse::ecs::ComponentInfo sinfo;
		Velocity2D(const Eigen::Affine2f& vel);
        Eigen::Affine2f velocity;
    };
    struct Velocity3D : public sparse::ecs::Component {
		static sparse::ecs::ComponentInfo sinfo;
		Velocity3D(const Eigen::Affine3f& vel);
        Eigen::Affine3f velocity;
    };
    struct PremulVelocity3D : sparse::ecs::Component {
		static sparse::ecs::ComponentInfo sinfo;
		PremulVelocity3D(const Eigen::Affine3f& vel);
        Eigen::Affine3f velocity;
    };
}
#endif
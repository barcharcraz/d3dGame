#include "Velocity.h"
namespace Components {
	using namespace sparse::ecs;
	ComponentInfo Velocity2D::sinfo = GenDefCompInfo<Velocity2D>();
	ComponentInfo Velocity3D::sinfo = GenDefCompInfo<Velocity3D>();
	ComponentInfo PremulVelocity3D::sinfo = GenDefCompInfo<PremulVelocity3D>();

	Velocity2D::Velocity2D(const Eigen::Affine2f& vel)
		: velocity(vel)
	{
		info = &Velocity2D::sinfo;
	}
	Velocity3D::Velocity3D(const Eigen::Affine3f& vel)
		: velocity(vel)
	{
		info = &Velocity3D::sinfo;
	}
	PremulVelocity3D::PremulVelocity3D(const Eigen::Affine3f& vel)
		: velocity(vel)
	{
		info = &PremulVelocity3D::sinfo;
	}
}
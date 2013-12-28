#include "Velocity.h"
namespace Components {
	Velocity3D::Velocity3D(const Eigen::Vector3f& lin, const Eigen::Quaternionf& rot) {
		linear = lin;
		angular = rot;
	}
	Velocity3D::Velocity3D(const Eigen::Affine3f& trans)
		: Velocity3D(trans.translation(), Eigen::Quaternionf(trans.rotation())) {}
	Velocity3D::Velocity3D(const Eigen::Vector3f& lin)
		: Velocity3D(lin, Eigen::Quaternionf::Identity()) {}
	Velocity3D::Velocity3D(const Eigen::Quaternionf& rot)
		: Velocity3D(Eigen::Vector3f::Identity(), rot) {}

	PremulVelocity3D::PremulVelocity3D(const Eigen::Vector3f& lin, const Eigen::Quaternionf& rot) {
		linear = lin;
		angular = rot;
	}
	PremulVelocity3D::PremulVelocity3D(const Eigen::Affine3f& trans)
		: PremulVelocity3D(trans.translation(), Eigen::Quaternionf(trans.rotation())) {}
	PremulVelocity3D::PremulVelocity3D(const Eigen::Vector3f& lin)
		: PremulVelocity3D(lin, Eigen::Quaternionf::Identity()) {}
	PremulVelocity3D::PremulVelocity3D(const Eigen::Quaternionf& rot)
		: PremulVelocity3D(Eigen::Vector3f::Identity(), rot) {}
}
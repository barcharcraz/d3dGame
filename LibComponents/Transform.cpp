#include "Transform.h"
namespace Components {
	Transform3D::Transform3D(const Eigen::Affine3f& trans)
		: Transform3D(trans.translation(), Eigen::Quaternionf(trans.rotation())) 
	{}
	Transform3D::Transform3D(const Eigen::Vector3f& trans)
		: Transform3D(trans, Eigen::Quaternionf::Identity()) {}
	Transform3D::Transform3D(const Eigen::Quaternionf& rot)
		: Transform3D(Eigen::Vector3f::Identity(), rot) {}
	Transform3D::Transform3D(const Eigen::Vector3f& trans, const Eigen::Quaternionf& rot)
		: position(trans), rotation(rot) {}
}
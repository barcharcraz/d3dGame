#ifndef LIBCOMPONENTS_AXISALIGNEDBB_H
#define LIBCOMPONENTS_AXISALIGNEDBB_H
#include "IComponent.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace Components {
	class AxisAlignedBB : public IComponent {
	public:
		AxisAlignedBB(const Eigen::AlignedBox3f& bbox);
		AxisAlignedBB(Eigen::AlignedBox3f && bbox);
		Eigen::AlignedBox3f RestAABB;
		Eigen::AlignedBox3f CurAABB;
	};
	class AxisAlignedBBUpdate : public IComponent {};
}

#endif
#ifndef LIBCOMPONENTS_AXISALIGNEDBB_H
#define LIBCOMPONENTS_AXISALIGNEDBB_H
#include <ecs.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Utils/event.h>
namespace Components {
	class AxisAlignedBB : public sparse::ecs::Component {
	public:
        static sparse::ecs::ComponentType stype;
		AxisAlignedBB(const Eigen::AlignedBox3f& bbox);
		Eigen::AlignedBox3f RestAABB;
		Eigen::AlignedBox3f CurAABB;
	};
	
}

#endif

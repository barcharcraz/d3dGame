#include <LibComponents/IComponent.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#ifndef LIBCOMPONENTS2D_RECTANGLE_H
#define LIBCOMPONENTS2D_RECTANGLE_H

namespace Components {
	class Rectangle : public IComponent {
	public:
		Rectangle(const Eigen::Vector2f& extent_arg);
		Eigen::Vector2f extent;
	};
}

#endif
#include <LibComponents/IComponent.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#ifndef LIBCOMPONENTS2D_RECTANGLE_H
#define LIBCOMPONENTS2D_RECTANGLE_H

namespace Components {
	class Rectangle : public IComponent {
	public:
		Rectangle(const Eigen::Vector2f& bottom_left_arg, const Eigen::Vector2f& top_right_arg);
		Eigen::Vector2f bottom_left;
		Eigen::Vector2f top_right;
	};
}

#endif
#include <LibComponents/IComponent.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#ifndef LIBCOMPONENTS2D_LINE_H
#define LIBCOMPONENTS2D_LINE_H

namespace Components {
	class Line : public IComponent {
	public:
		Line(const Eigen::Vector2f& a_arg, const Eigen::Vector2f& b_arg);
		Line(const Eigen::Vector2f& b_arg);
		Eigen::Vector2f a;
		Eigen::Vector2f b;
	};
}

#endif
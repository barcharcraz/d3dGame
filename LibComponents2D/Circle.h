#include <LibComponents/IComponent.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#ifndef LIBCOMPONENTS2D_CIRCLE_H
#define LIBCOMPONENTS2D_CIRCLE_H

namespace Components {
	class Circle : public IComponent {
	public:
		Circle(const Eigen::Vector2f& center, float radius);
		explicit Circle(float radius);
		
		Eigen::Vector2f center;
		float radius;
	};
}

#endif
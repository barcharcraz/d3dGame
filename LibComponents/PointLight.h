#ifndef LIBCOMPONENTS_POINTLIGHT_H
#define LIBCOMPONENTS_POINTLIGHT_H
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "IComponent.h"
namespace Components {
	class PointLight : public IComponent {
	public:
		PointLight();
		explicit PointLight(const Eigen::Vector4f& color);
		explicit PointLight(unsigned int radius);
		PointLight(const Eigen::Vector4f& color, unsigned int radius);
		
		struct Data {
			Eigen::Vector4f color;
			unsigned int radius;
		};
		Data data;
		Eigen::Vector4f& Color;
		unsigned int& Radius;
		
	};
}

#endif

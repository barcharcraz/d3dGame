#ifndef LIBCOMPONENTS_POINTLIGHT_H
#define LIBCOMPONENTS_POINTLIGHT_H
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "IComponent.h"
namespace Components {
	class PointLight : public IComponent {
	public:
		PointLight();
		explicit PointLight(const Eigen::Vector4f& diffuse);
		explicit PointLight(unsigned int radius);
		PointLight(const Eigen::Vector4f& diffuse, unsigned int radius);
		
		Eigen::Vector4f Diffuse;
		unsigned int Radius;
		
	};
}

#endif

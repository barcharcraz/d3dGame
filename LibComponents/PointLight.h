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
		PointLight(const Eigen::Vector4f& diffuse, const Eigen::Vector4f& specular, unsigned int radius);
		PointLight(const Eigen::Vector4f& diffuse, unsigned int radius);
		explicit PointLight(unsigned int radius);
		
		Eigen::Vector4f Diffuse;
		Eigen::Vector4f Specular;
		unsigned int Radius;
		
	};
}

#endif

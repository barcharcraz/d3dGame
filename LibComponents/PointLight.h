#ifndef LIBCOMPONENTS_POINTLIGHT_H
#define LIBCOMPONENTS_POINTLIGHT_H
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <ecs.h>
namespace Components {
	class PointLight : public sparse::ecs::Component {
	public:
		static sparse::ecs::ComponentInfo sinfo;
		PointLight();
		explicit PointLight(const Eigen::Vector4f& diffuse);
		PointLight(const Eigen::Vector4f& diffuse, unsigned int radius);
		explicit PointLight(unsigned int radius);
		PointLight(const Eigen::Vector4f& diffuse, const Eigen::Vector4f& specular, unsigned int radius);

		Eigen::Vector4f Diffuse;
		Eigen::Vector4f Specular;
		unsigned int Radius;
		
	};
}

#endif

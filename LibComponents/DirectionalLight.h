#ifndef LIBCOMPONENTS_DIRECTIONALLIGHT_H
#define LIBCOMPONENTS_DIRECTIONALLIGHT_H
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <ecs.h>
namespace Components {
	class DirectionalLight : public sparse::ecs::Component {
	public:
        static sparse::ecs::ComponentType stype;
		DirectionalLight(const Eigen::Vector4f& color, const Eigen::Vector4f& dir_arg);
		DirectionalLight(const Eigen::Vector4f& diffuse_arg, const Eigen::Vector4f& specular_arg, const Eigen::Vector4f& dir_arg);
		Eigen::Vector4f Diffuse;
		Eigen::Vector4f Specular;
		Eigen::Vector4f Direction;
	};
}

#endif

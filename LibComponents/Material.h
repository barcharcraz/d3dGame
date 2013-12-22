#ifndef LIBCOMPONENTS_MATERIAL_H
#define LIBCOMPONENTS_MATERIAL_H
#include <ecs.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include <memory>
namespace Components {
	class Material : public sparse::ecs::Component {
	public:
        static sparse::ecs::ComponentInfo stype;
		Material(const Eigen::Vector4f& ambiang_arg, const Eigen::Vector4f& diffuse_arg, const Eigen::Vector4f& specular_arg, float shine_arg);
		struct Data {
			Eigen::Vector4f ambiant;
			Eigen::Vector4f diffuse;
			Eigen::Vector4f specular;
			float shine;
		} data;
		
	};
}


#endif

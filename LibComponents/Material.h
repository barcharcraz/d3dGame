#ifndef LIBCOMPONENTS_MATERIAL_H
#define LIBCOMPONENTS_MATERIAL_H
#include "IComponent.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

#include <memory>
namespace Components {
	class Material : public IComponent {
	public:
		Material(const Eigen::Vector4f& ambiang_arg, const Eigen::Vector4f& diffuse_arg);
		struct Data {
			Eigen::Vector4f ambiant;
			Eigen::Vector4f diffuse;
		};
		Data data;
		Eigen::Vector4f& Ambiant;
		Eigen::Vector4f& Diffuse;

	};
}


#endif
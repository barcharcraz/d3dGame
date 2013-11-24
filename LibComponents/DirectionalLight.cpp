#include "DirectionalLight.h"
namespace Components {
	DirectionalLight::DirectionalLight(const Eigen::Vector4f& diffuse, const Eigen::Vector4f& dir_arg)
		: Diffuse(diffuse), Specular(Eigen::Vector4f{0.0f, 0.0f, 0.0f, 0.0f}), Direction(dir_arg)
	{

	}
	DirectionalLight::DirectionalLight(const Eigen::Vector4f& diffuse_arg, 
		const Eigen::Vector4f& specular_arg, const Eigen::Vector4f& dir_arg)
		: Diffuse(diffuse_arg), Specular(specular_arg), Direction(dir_arg)
	{

	}
}
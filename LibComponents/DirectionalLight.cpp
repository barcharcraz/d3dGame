#include "DirectionalLight.h"
namespace Components {
	DirectionalLight::DirectionalLight(const Eigen::Vector4f& diffuse)
		: Diffuse(diffuse), Specular(Eigen::Vector4f{0.0f, 0.0f, 0.0f, 0.0f})
	{

	}
	DirectionalLight::DirectionalLight(const Eigen::Vector4f& diffuse_arg, const Eigen::Vector4f& specular_arg)
		: Diffuse(diffuse_arg), Specular(specular_arg)
	{

	}
}
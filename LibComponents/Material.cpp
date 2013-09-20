#include "stdafx.h"
#include "Material.h"

namespace Components {
	Material::Material(
		const Eigen::Vector4f& ambiant_arg, 
		const Eigen::Vector4f& diffuse_arg, 
		const Eigen::Vector4f& specular_arg, float shine_arg) 
		: Ambiant(data.ambiant), Diffuse(data.diffuse), Specular(data.specular), Shine(data.shine)
	{
		data.ambiant = ambiant_arg;
		data.diffuse = diffuse_arg;
		data.specular = specular_arg;
		data.shine = shine_arg;
	}
}
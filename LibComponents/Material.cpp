#include "stdafx.h"
#include "Material.h"

namespace Components {
	Material::Material(const Eigen::Vector4f& ambiant_arg, const Eigen::Vector4f& diffuse_arg) 
		: Ambiant(data.ambiant), Diffuse(data.diffuse)
	{
		data.ambiant = ambiant_arg;
		data.diffuse = diffuse_arg;
	}
}
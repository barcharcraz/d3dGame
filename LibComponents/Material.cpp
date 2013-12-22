#include "stdafx.h"
#include "Material.h"

namespace Components {
	Material::Material(
		const Eigen::Vector4f& ambiant_arg, 
		const Eigen::Vector4f& diffuse_arg, 
		const Eigen::Vector4f& specular_arg, float shine_arg) 
	{
        this->info = &Material::stype;
		this->data = { ambiant_arg, diffuse_arg, specular_arg, shine_arg };
	}
}

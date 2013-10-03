#include "Data.h"
#include "Entity.h"
#include <LibComponents/Transform.h>
#include <LibComponents/PointLight.h>
#include <LibComponents/DirectionalLight.h>
namespace LibCommon {
    std::vector<Eigen::Vector4f> fuse_verts(const std::vector<Vertex>& verts) {
        std::vector<Eigen::Vector4f> rv;
        rv.reserve(verts.size());
        for(auto& elm : verts) {
            //we move here since we copied in the loop!
            rv.push_back(elm.pos);
        }
        return rv;
    }
	std::vector<point_light> fuse_point_lights(const std::vector<Entity*>& lights) {
		std::vector<point_light> retval;
		for (auto elm : lights) {
			auto transform = elm->Get<Components::Transform3D>();
			auto light = elm->Get<Components::PointLight>();
			point_light new_light;
			new_light.diffuse = light->Diffuse;
			new_light.position << transform->transform.translation(), 1.0f;
			retval.push_back(std::move(new_light));
		}
		return retval;
	}
	std::vector<directional_light> fuse_dir_lights(const std::vector<Entity*>& lights) {
		std::vector<directional_light> retval;
		for (auto elm : lights) {
			auto transform = elm->Get<Components::Transform3D>();
			auto light = elm->Get<Components::DirectionalLight>();
			directional_light new_light;
			new_light.diffuse = light->Diffuse;
			new_light.specular = light->Specular;
			Eigen::Vector4f direction = Eigen::Vector4f::UnitY();
			Eigen::Affine3f rotation(transform->transform.rotation());
			direction = rotation * direction;
			direction.normalize();
			new_light.direction = direction;
			retval.push_back(std::move(new_light));
		}
		return retval;
	}
}

#include "Data.h"
#include "Entity.h"
#include <LibComponents/Transform.h>
#include <LibComponents/PointLight.h>
#include <LibComponents/DirectionalLight.h>
namespace LibCommon {
	std::vector<point_light> fuse_point_lights(const std::vector<Entity*>& lights) {
		std::vector<point_light> retval;
		for (auto elm : lights) {
			auto transform = elm->Get<Components::Transform3D>();
			auto light = elm->Get<Components::PointLight>();
			point_light new_light;
			new_light.diffuse = light->Diffuse;
			new_light.position = transform->transform.translation();
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
			auto direction = Eigen::Vector3f::UnitY();
			direction *= transform->transform.rotation();
			direction.normalize();
			new_light.direction = std::move(direction);
			retval.push_back(std::move(new_light));
		}
		return retval;
	}
}
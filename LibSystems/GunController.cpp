#include "stdafx.h"
#include "GunController.h"
#include <LibInput/Input.h>
#include <LibImage/ImageLoader.h>
#include <LibComponents/Transform.h>
#include <LibComponents/GunDefinition.h>
#include <LibCommon/Scene.h>
#include <LibCommon/Entity.h>
#include <LibPrefabs/EnergyBullet.h>
namespace Systems {
	GunController::GunController()
		: System({ typeid(Input::Input), typeid(Components::Transform3D), typeid(Components::GunDefinition) })
	{
		priority = LibCommon::Priority::MEDIUM;
	}
	void GunController::Process(LibCommon::Entity* e) {
		using namespace Components;
		using namespace Eigen;
		auto position = e->Get<Transform3D>();
		auto def = e->Get<GunDefinition>();
		auto inp = e->Get<Input::Input>();
		Eigen::Vector3f vel = -Eigen::Vector3f::UnitZ() * def->velocity;
		vel = position->rotation.inverse() * vel;
		if (inp->Action("Fire")) {
			auto ent = parent->AddEntity<Prefabs::EnergyBullet>(5.0f, 5.0f,
				Image::GetImageData(def->texPath),
				vel.head<3>().eval(), def->time_to_live);
			auto transform = ent->Get<Transform3D>();
			transform->position = position->position;
			
		}
	}
}
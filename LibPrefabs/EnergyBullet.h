#ifndef LIBPREFABS_ENERGYBULLET_H
#define LIBPREFABS_ENERGYBULLET_H
#include <LibCommon/Entity.h>
#include <LibComponents/Texture.h>
namespace Prefabs {
	class EnergyBullet : public LibCommon::Entity {
	public:
		EnergyBullet(float width, float height, const Components::Texture& tex);
	};
}


#endif
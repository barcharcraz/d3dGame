#ifndef LIBPREFABS_SKYDOME_H
#define LIBPREFABS_SKYDOME_H
#include <LibCommon/Entity.h>
#include <LibComponents/Texture.h>
namespace Prefabs {
    class SkyDome : public LibCommon::Entity {
    public:
        SkyDome(float radius, const Components::Texture& tex);
    };
}

#endif

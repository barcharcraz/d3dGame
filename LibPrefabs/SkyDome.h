#ifndef LIBPREFABS_SKYDOME_H
#define LIBPREFABS_SKYDOME_H
#include <LibCommon/Entity.h>
#include <LibComponents/Texture.h>
#include <LibComponents/ParentLink.h>
namespace Prefabs {
    class SkyDome : public LibCommon::Entity {
    public:
        SkyDome(float radius, const Components::Texture& tex, Components::ParentLink* parent);
    };
}

#endif

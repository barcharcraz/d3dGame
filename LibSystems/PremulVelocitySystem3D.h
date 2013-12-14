#ifndef LIBSYSTEMS_PREMULVELOCITYSYSTEM3D_H
#define LIBSYSTEMS_PREMULVELOCITYSYSTEM3D_H
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
namespace Systems {
    class PremulVelocitySystem3D : public LibCommon::System {
    public:
        PremulVelocitySystem3D();
        virtual void Process(LibCommon::Entity* e) override;
    };
}

#endif
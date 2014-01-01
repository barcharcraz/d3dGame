#ifndef LIBCOMPONENTS_ICOMPONENT_H
#define LIBCOMPONENTS_ICOMPONENT_H
#include "stdafx.h"
#include <functional>
namespace LibCommon {
    class Entity;
}
namespace Components {

    class IComponent {
    public:
        LibCommon::Entity* ent = nullptr;
        virtual ~IComponent() = 0;
    };
    inline IComponent::~IComponent() {}
}
#endif

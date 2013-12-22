#include "Effect.h"

namespace Components {
    sparse::ecs::ComponentInfo Effect::stype = sparse::ecs::GenDefCompInfo<Effect>();
    Effect::Effect(const Effects::Effect& effect_arg)
        : effect(effect_arg)
    {
        init();
    }
    void Effect::init() {
        info = &Effect::stype;
    }
}

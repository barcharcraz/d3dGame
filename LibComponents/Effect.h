#ifndef LIBCOMPONENTS_EFFECT_H
#define LIBCOMPONENTS_EFFECT_H
#include <LibEffects/Effect.h>
#include <ecs.h>
namespace Components {
	class Effect : public sparse::ecs::Component {
	public:
        static sparse::ecs::ComponentInfo stype;
		Effect(const Effects::Effect& effect_arg);
        Effects::Effect effect;
    private:
        void init();
	};
}

#endif

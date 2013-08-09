#ifndef LIBCOMPONENTS_EFFECT_H
#define LIBCOMPONENTS_EFFECT_H
#include <LibEffects/Effect.h>
#include "IComponent.h"
namespace Components {
	class Effect : public Effects::Effect, public IComponent {
	public:
		//fake inhereting constructor
		template<typename... Args>
		Effect(Args&&... args)
			: Effects::Effect(std::forward<Args>(args)...)
		{

		}
	};
}

#endif
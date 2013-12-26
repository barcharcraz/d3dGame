#ifndef LIBCOMPONENTS_GUNDEFINITION_H
#define LIBCOMPONENTS_GUNDEFINITION_H
#include <LibEffects/Effect.h>
#include "IComponent.h"
#include <chrono>
namespace Components {
	class GunDefinition : public IComponent {
	public:
		GunDefinition(const std::string& texPath,
			float vel,
			std::chrono::milliseconds lifetime);
		std::string texPath;
		float velocity;
		std::chrono::milliseconds time_to_live;
	};
}

#endif
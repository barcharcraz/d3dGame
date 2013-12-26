#include "GunDefinition.h"

namespace Components {
	GunDefinition::GunDefinition(const std::string& tex,
		float vel,
		std::chrono::milliseconds lifetime)
		: texPath(tex), velocity(vel), time_to_live(lifetime)
	{}
}
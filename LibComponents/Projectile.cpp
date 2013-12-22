#include "Projectile.h"

namespace Components {
	Projectile::Projectile(float damage_arg, std::chrono::milliseconds time_arg)
		: damage(damage_arg), time_to_live(time_arg)
	{
		info = &Projectile::sinfo;
	}
}
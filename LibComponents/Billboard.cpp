#include "Billboard.h"

namespace Components {
    sparse::ecs::ComponentInfo Billboard::stype = sparse::ecs::GenDefCompInfo<Billboard>();
	Billboard::Billboard ( float width_arg, float height_arg )
		: width(width_arg), height(height_arg) 
	{
        info = &Billboard::stype;
	}

}

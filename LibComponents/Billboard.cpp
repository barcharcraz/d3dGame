#include "Billboard.h"

namespace Components {
    sparse::ecs::ComponentType Billboard::stype = sparse::ecs::GenID();
	Billboard::Billboard ( float width_arg, float height_arg )
		: width(width_arg), height(height_arg) 
	{
        this->size = sizeof(Billboard);
        type = Billboard::stype;
	}

}

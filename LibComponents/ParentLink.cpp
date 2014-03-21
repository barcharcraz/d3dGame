#include "ParentLink.h"
namespace Components {
    ParentLink::ParentLink ( Transform3D* src, ParentLink* par, parent_type type_arg ) 
        : parent(par), transform_src(src), type(type_arg)
    {

    }

}
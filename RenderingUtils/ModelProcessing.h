//!\ brief the functions in ModelProcessing
//! are for going from one kind of data to a model
//! that can be rendered
#ifndef RENDERINGUTILS_MODELPROCESSING_H
#define RENDERINGUTILS_MODELPROCESSING_H
#include <LibComponents/Model.h>
#include <LibComponents/Billboard.h>
#include <LibCommon/Data.h>
namespace utils {
	Components::Model generate_quad(float width, float height);
    Components::Model generate_icosahedron(float radius);
}


#endif

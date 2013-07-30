#ifndef LIBCOMPONENTS_MODEL_H
#define LIBCOMPONENTS_MODEL_H
#include "IComponent.h"
#include <LibCommon/Data.h>
#include <vector>
namespace Components {
	struct Model : public IComponent {
		Model(const std::vector<LibCommon::Vertex>& vertex, const std::vector<int>& index)
			: verts(vertex), indices(index) {}
		Model() {}
		std::vector<LibCommon::Vertex> verts;
		std::vector<int> indices;
	};
}
#endif
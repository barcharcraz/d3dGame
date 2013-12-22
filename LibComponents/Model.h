#ifndef LIBCOMPONENTS_MODEL_H
#define LIBCOMPONENTS_MODEL_H
#include <ecs.h>
#include <LibCommon/Data.h>
#include <LibAssets/GeometryFile.h>
#include <vector>
namespace Components {
	struct Model : public sparse::ecs::Component {
        static sparse::ecs::ComponentInfo sinfo;
		Model(const std::vector<LibCommon::Vertex>& vertex, const std::vector<unsigned int>& index);
		Model(const Assets::GeometryFile& file);
		Model();
		std::vector<LibCommon::Vertex> verts;
		std::vector<unsigned int> indices;
	};
}
#endif

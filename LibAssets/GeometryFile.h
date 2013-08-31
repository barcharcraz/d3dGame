#ifndef LIBASSETS_MODEL_H
#define LIBASSETS_MODEL_H
#include <vector>
#include <LibCommon/Data.h>
namespace Assets {
	class GeometryFile {
	public:
		virtual std::vector<int>& Indices() = 0;
		virtual std::vector<LibCommon::Vertex>& Verts() = 0;
	};
}

#endif
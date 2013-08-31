#ifndef LIBASSETS_MODEL_H
#define LIBASSETS_MODEL_H
#include <vector>
#include <LibCommon/Data.h>
namespace Assets {
	class GeometryFile {
	public:
		virtual const std::vector<unsigned int>& Indices() const = 0;
		virtual const std::vector<LibCommon::Vertex>& Verts() const = 0;
	};
}

#endif
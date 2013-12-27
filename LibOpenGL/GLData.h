#ifndef LIBOPENGL_GLDATA_H
#define LIBOPENGL_GLDATA_H
#include "GLBuffer.h"
#include "GLAttribArray.h"
#include <memory>
namespace LibOpenGL {
	struct buffers {
		buffers() = default;
		buffers(const buffers&) = delete;
		buffers(buffers&& other)
			: Uniform(std::move(other.Uniform)),
			Vertex(std::move(other.Vertex)),
			Index(std::move(other.Index)),
			vao(std::move(other.vao)) {}
		GLBuffer Uniform;
		GLBuffer Vertex;
		GLBuffer Index;
		GLAttribArray vao;
	};
}

#endif
#include "GLUtils.h"
#include <cstdio>
#include <system_error>
namespace LibOpenGL {
	const char* EnumString(GLenum val) {
		switch (val)
		{
		case gl::INVALID_ENUM:
			return "GL_INVALID_ENUM";
		default:
			return "ENUM NOT RECOGNISED";
		}
	}
	void CheckError() {
		GLenum err;
		err = gl::GetError();
		if (err != gl::NO_ERROR_) {
			fprintf(stderr, "OpenGL error %u: %s", err, EnumString(err));
			throw std::system_error(err, std::system_category());
		}
	}
}
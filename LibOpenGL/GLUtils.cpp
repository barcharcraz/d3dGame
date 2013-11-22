#include "GLUtils.h"
#include <cstdio>
#include <system_error>
namespace LibOpenGL {
	const char* EnumString(GLenum val) {
		switch (val)
		{
		case gl::INVALID_ENUM:
			return "GL_INVALID_ENUM";
        case gl::INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case gl::INVALID_VALUE:
            return "GL_INVALID_VALUE";
		default:
			return "ENUM NOT RECOGNISED";
		}
	}
	void CheckError() {
		GLenum err;
		err = gl::GetError();
		if (err != gl::NO_ERROR_) {
            const char* errStr = EnumString(err);
			fprintf(stderr, "OpenGL error %u: %s", err, errStr);
			throw std::system_error(err, std::system_category());
		}
	}
}

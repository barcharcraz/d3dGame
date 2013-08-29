#include "stdafx.h"
#include "OpenGLRenderer.h"
#include <Utils/exceptions.h>

namespace LibOpenGL {
	OpenGLRenderer::OpenGLRenderer() {
		auto res = gl::sys::LoadFunctions();
		if(!res) {
			throw utils::graphics_api_error("could not load OGL functions");
		}
	}

}
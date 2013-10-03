#include "stdafx.h"
#include "OpenGLRenderer.h"
#include <Utils/exceptions.h>
#include <system_error>
namespace LibOpenGL {
	OpenGLRenderer::OpenGLRenderer() {
		auto res = gl::sys::LoadFunctions();
        
		if(!res) {
			throw utils::graphics_api_error("could not load OGL functions");
		}
        EnableDepthBuffer();
		//glCreateProgram is garenteed to return a non-zero value
		//so zero is a good "null" value
		ActiveProgram = 0;
	}

    //freestanding functions
    void EnableDepthBuffer() {
        gl::Enable(gl::DEPTH_TEST);
        gl::DepthFunc(gl::LEQUAL);
        gl::DepthMask(gl::TRUE_);
        gl::DepthRange(0.0f, 1.0f);
    }
    void DisableDepthBuffer() {
        gl::Disable(gl::DEPTH_TEST);
    }
	void CheckError() {
		GLenum err;
		err = gl::GetError();
		if (err != gl::NO_ERROR_) {
			throw std::system_error(err, std::system_category());
		}
	}

}

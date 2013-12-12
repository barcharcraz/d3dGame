#include "stdafx.h"
#include "OpenGLRenderer.h"
#include <Utils/exceptions.h>
#include <system_error>
namespace LibOpenGL {
	
    OpenGLRenderer::OpenGLRenderer(windowing::IGLWindow* win)
        : _win(win)
    {
        init();
    }
    //PRIVATE
    void OpenGLRenderer::init() {
        _win->MakeGLActive();
        auto res = gl::sys::LoadFunctions();
        if(!res) {
            throw utils::graphics_api_error("could not load OGL functions");
        }
        EnableDepthBuffer();
        //we are using zero as a "null" value, since
        //gl will not return that when creating a program
        ActiveProgram = 0;
    }
    void OpenGLRenderer::Present() {
        _win->Present();
    }
    void OpenGLRenderer::Clear() {
        gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT | gl::STENCIL_BUFFER_BIT);
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

}

#include "stdafx.h"
#include "OpenGLRenderer.h"
#include <Utils/exceptions.h>
#include <system_error>
namespace LibOpenGL {
	
    OpenGLRenderer::OpenGLRenderer(windowing::IGLWindow* win)
        : _win(win)
    {
        _win->MakeGLActive();
        init();
    }
    OpenGLRenderer::OpenGLRenderer() {
    }
    OpenGLRenderer::~OpenGLRenderer() {
        Detach();
    }
    void OpenGLRenderer::Attach(windowing::IGLWindow* target) {
        if (nullptr != _win) {
            Detach();
        }
        _win = target;
        _win->MakeGLActive();
        init();
    }
    void OpenGLRenderer::Detach() {
        if (_win == nullptr) {
            return;
        }
        _win->MakeGLInactive();
        _win = nullptr;
        
    }
    //PRIVATE
    void OpenGLRenderer::init() {

        auto res = gl::sys::LoadFunctions();
        if(!res) {
            throw utils::graphics_api_error("could not load OGL functions");
        }
        EnableDepthBuffer();
        //we are using zero as a "null" value, since
        //gl will not return that when creating a program
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

}

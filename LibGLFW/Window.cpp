#include "stdafx.h"
#include "Window.h"
#include <stdexcept>
#include <chrono>
#include <thread>
#include <iostream>
#include <LibInput/Input.h>
namespace LibGLFW {
    namespace {
        Window* ActiveWindow;
        void resizeWindow(GLFWwindow* win, int w, int h);
        
        void resizeWindow(GLFWwindow* win, int w, int h) {
            glViewport(0,0,w,h);
        }
    }

    void HandleKey(GLFWwindow* win, int key, int scancode, int action, int mods) {

    }
    int Run() {
        glfwMakeContextCurrent(ActiveWindow->_win);
        glfwSwapInterval(2);
        while(!glfwWindowShouldClose(ActiveWindow->_win)) { 
            if(ActiveWindow->update) {
				ActiveWindow->update();
			}
			glfwSwapBuffers(ActiveWindow->_win);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            glfwPollEvents();
        }
        glfwTerminate();
        return 0;
    }
	Window::Window() {
		init(640,480);
	}

    Window::Window( void* ) {
        init(640, 480);
    }
    
    Window::Window(int w, int h) {
        init(w, h);
    }
    Window::~Window() {
        if(ActiveWindow == this) {
            ActiveWindow = nullptr;
        }
        glfwDestroyWindow(_win);
    }
    void Window::AttachInput(Input::Input* in) {
        _input = in; 
    }
    void Window::Show() {
        return; //we dont need to do anything for GLFW
    }
    void Window::SetAsActive() {
        glfwMakeContextCurrent(_win);
        glfwSetWindowSizeCallback(_win, &resizeWindow);
        ActiveWindow = this;
    }

    /* -----------PRIVATE------------- */
    void Window::init(int w, int h) {
        int result = 0;
        result = glfwInit();
        if(!result) {
            throw std::runtime_error("could not initialize glfw");
        }
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        _win = glfwCreateWindow(w, h, "GLFW Winodow", nullptr, nullptr);
        if(!_win) {
            throw std::runtime_error("could not create a GLFW window");
        }
        SetAsActive();
        glViewport(0,0,w,h);
    }
}

#include "stdafx.h"
#include "Window.h"
#include "Keys.h"
#include <stdexcept>
#include <chrono>
#include <thread>
#include <iostream>
#include <LibInput/Input.h>
#include <LibInput/DeviceTypes.h>
namespace LibGLFW {
    namespace {
        Window* ActiveWindow;
        void resizeWindow(GLFWwindow*, int w, int h);
		void reportGlfwError(int code, const char* error);
        void resizeWindow(GLFWwindow*, int w, int h) {
            glViewport(0,0,w,h);
        }
        void reportGlfwError(int code, const char* error) {
            std::string err(error);
            std::cout << "GLFW Error with code: " <<
            code << " and description: " << err << std::endl;
            throw std::runtime_error(err);
        }
		
		
    }

	void HandleKey(GLFWwindow*, int key, int, int action, int) {
		
		if (nullptr == ActiveWindow) {
			return;
		}
		auto keyItr = glfw_keymap.find(key);
		if (keyItr == glfw_keymap.end()) {
			return;
		}
		if (GLFW_PRESS == action) {
			ActiveWindow->_input->ActivateKey(keyItr->second);
		} else if (GLFW_RELEASE == action) {
			ActiveWindow->_input->DeactivateKey(keyItr->second);
		}
	}
	void HandleCursorEnter(GLFWwindow* win, int entered) {
		if (ActiveWindow != nullptr && ActiveWindow->_win == win) {
			if (GL_TRUE == entered) {
				double newX, newY;
				glfwGetCursorPos(win, &newX, &newY);
				ActiveWindow->lastX = newX;
				ActiveWindow->lastY = newY;
			}
		}
	}
    int Run() {
        glfwMakeContextCurrent(ActiveWindow->_win);
        glfwSwapInterval(1);
        
        while(!glfwWindowShouldClose(ActiveWindow->_win)) { 
            if(ActiveWindow->update) {
				ActiveWindow->update();
			}
			ActiveWindow->HandleMouseMovement();
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
		glfwSetKeyCallback(_win, &HandleKey);
    }
    void Window::Show() {
        return; //we dont need to do anything for GLFW
    }
    void Window::Present() {
        glfwSwapBuffers(_win);
    }
    void Window::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
    void Window::SetAsActive() {
        glfwMakeContextCurrent(_win);
        glfwSetWindowSizeCallback(_win, &resizeWindow);
		glfwSetCursorEnterCallback(_win, &HandleCursorEnter);
		glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        ActiveWindow = this;
    }
    
    /* -----------PRIVATE------------- */
    void Window::init(int w, int h) {
        glfwSetErrorCallback(&reportGlfwError);
        int result = 0;
        result = glfwInit();
        if(!result) {
            throw std::runtime_error("could not initialize glfw");
        }
        
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        _win = glfwCreateWindow(w, h, "GLFW Winodow", nullptr, nullptr);
        if(!_win) {
            throw std::runtime_error("could not create a GLFW window");
        }
        SetAsActive();
        glViewport(0,0,w,h);
    }
	void Window::HandleMouseMovement() {
		if (_input != nullptr) {
			double x, y = 0;
			int winx, winy = 0;
			double dx, dy;
			glfwGetCursorPos(_win, &x, &y);
			glfwGetWindowSize(_win, &winx, &winy);
			dx = lastX - x;
			dy = lastY - y;
			lastX = x;
			lastY = y;
			auto mouse = _input->Device(Input::MouseType);
			mouse->axes[Input::AxisName::X].SetPosition(dx/winx);
			mouse->axes[Input::AxisName::Y].SetPosition(dy/winy);
		}
	}
}

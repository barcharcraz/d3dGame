#include "stdafx.h"
#include "Window.h"
#include <stdexcept>
namespace LibGLFW {
    int Run() {
        while(!glfwWindowShouldClose(ActiveWindow->_win)) {
            if(ActiveWindow->update) {
                ActiveWindow->update();
            }
            glfwPollEvents();
        }
    }
    Window::Window() {
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
    void Window::SetAsActive() {
        glfwMakeContextCurrent(_win);
        ActiveWindow = this;
    }
    /* -----------PRIVATE------------- */
    void Window::init(int w, int h) {
        int result = 0;
        result = glfwInit();
        if(!result) {
            throw std::runtime_error("could not initialize glfw");
        }
        _win = glfwCreateWindow(w, h, "GLFW Winodow", nullptr, nullptr);
        if(!_win) {
            throw std::runtime_error("could not create a GLFW window");
        }
        glfwMakeContextCurrent(_win);
    }
}
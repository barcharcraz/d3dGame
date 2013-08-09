#include "stdafx.h"
#include "Window.h"
#include <stdexcept>
#include <chrono>
#include <thread>
namespace LibGLFW {
    static Window* ActiveWindow;
    int Run() {
        using namespace std::chrono;
        high_resolution_clock::time_point last_frame;
        last_frame = high_resolution_clock::now();
        milliseconds frameMax(16);
        while(!glfwWindowShouldClose(ActiveWindow->_win)) {
            high_resolution_clock::time_point target_time = high_resolution_clock::now() + frameMax;
            if(ActiveWindow->update) {
                ActiveWindow->update();
            }
            glfwPollEvents();
            auto remaining = target_time - high_resolution_clock::now();
            if(remaining > high_resolution_clock::duration(0)) {
                std::this_thread::sleep_for(remaining);
            }
            
            
        }
        glfwTerminate();
        return 0;
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
    void Window::Show() {
        return; //we dont need to do anything for GLFW
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
        SetAsActive();
    }
}
/*
* this file implements needed native access functions for windows
*/
#include "Window.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>
namespace LibGLFW {
    void* Window::Handle() {
        return glfwGetWin32Window(this->_win);
    }
}


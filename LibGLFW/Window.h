#ifndef LIBGLFW_WINDOW_H
#define LIBGLFW_WINDOW_H
#include <GLFW/glfw3.h>
#include <functional>
namespace LibGLFW {
    
    int Run();
    class Window {
        friend int Run();
    public:
        Window();
        ~Window();
        Window(int w ,int h);
        void Show();
        //! \brief note that this function
        //! sets a given context as the OpenGL
        //! current context as well, note that this is
        //! an OpenGL window specific function
        void SetAsActive();
        std::function<void()> update;
    private:
        void init(int w, int h);
        GLFWwindow *_win;
    };
    
    
}

#endif
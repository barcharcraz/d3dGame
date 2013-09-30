#ifndef LIBGLFW_WINDOW_H
#define LIBGLFW_WINDOW_H
#include <GLFW/glfw3.h>
#include <functional>
namespace Input {
    class Input;
}
namespace LibGLFW {
    void HandleKey(GLFWwindow* win, int key, int scancode, int action, int mods);
    int Run();
    class Window {
        friend int Run();
    public:
        Window(void*);
		Window();
        ~Window();
        Window(int w ,int h);
        void AttachInput(Input::Input* in);
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
        Input::Input* _input;
    };
    
    
}

#endif

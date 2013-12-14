#ifndef LIBGLFW_WINDOW_H
#define LIBGLFW_WINDOW_H
#include <GLFW/glfw3.h>
#include <functional>
#include <windowing/IWindow.h>
namespace Input {
    class Input;
}
namespace LibGLFW {
    void HandleKey(GLFWwindow* win, int key, int scancode, int action, int mods);
    void HandleCursorEnter(GLFWwindow* win, int entered);
    int Run();
    class Window : public windowing::IGLWindow {
        friend void HandleKey(GLFWwindow*, int, int, int, int);
        friend void HandleCursorEnter(GLFWwindow*, int);
        friend int Run();
    public:
        Window(void*);
        Window();
        ~Window();
        Window(int w ,int h);
        virtual void AttachInput(Input::Input* in) override;
        virtual void Show() override;
        virtual void Present() override;
        virtual void Clear() override;
        virtual void MakeGLActive() override;
        virtual void MakeGLInactive() override;
        //! \brief note that this function
        //! sets a given context as the OpenGL
        //! current context as well, note that this is
        //! an OpenGL window specific function
        void SetAsActive();
        // \brief initializes OpenGL and sets
        // this window as active, this is NOT
        // called be default as one may want to
        // use a GLFW window with direct3D
        std::function<void()> update;
    private:
        double lastX = 0;
        double lastY = 0;
        void HandleMouseMovement();
        void init(int w, int h);
        GLFWwindow *_win = nullptr;
        Input::Input* _input = nullptr;
    };
    
    
}

#endif

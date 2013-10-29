#ifndef LIBGLFW_WINDOW_H
#define LIBGLFW_WINDOW_H
#include <GLFW/glfw3.h>
#include <functional>
namespace Input {
    class Input;
}
namespace LibGLFW {
	void HandleKey(GLFWwindow* win, int key, int scancode, int action, int mods);
	void HandleCursorEnter(GLFWwindow* win, int entered);
    int Run();
    class Window {
		friend void HandleKey(GLFWwindow*, int, int, int, int);
		friend void HandleCursorEnter(GLFWwindow*, int);
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
        //! \brief get the handle to the window.
        //! in this case it is a GLFWwindow pointer
        GLFWwindow* Handle();
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

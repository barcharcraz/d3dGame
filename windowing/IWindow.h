#ifndef WINDOWING_IWINDOW
#define WINDOWING_IWINDOW
namespace Input {
    class Input;
}
namespace windowing {
    class IWindow {
    public:
        virtual void AttachInput(Input::Input* in) = 0;
        virtual void Show() = 0;
        virtual void Present() = 0;
        virtual void Clear() = 0;
    };
    class IGLWindow : public virtual IWindow {
    public:
        virtual void MakeGLActive() = 0;
        virtual void MakeGLInactive() = 0;
    };
    class IDXWindow : public virtual IWindow {
    public:
        virtual void* Handle() = 0;
        virtual void SetPresentOverride(std::function<void()> present) = 0;
        virtual void SetClearOverride(std::function<void()> clear) = 0;
    };
    class IMultiWindow : public IDXWindow, public IGLWindow {};
}

#endif

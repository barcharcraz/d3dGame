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
	};
    class IGLWindow : public IWindow {
    public:
        virtual void Present() = 0;
        virtual void Clear() = 0;
        virtual void AttachInput(Input::Input* in) = 0;
        virtual void Show() = 0;
        
    };
	class IDXWindow : public IWindow {
	public:
		virtual void AttachInput(Input::Input* in) = 0;
		virtual void Show() = 0;
		virtual void* Handle() = 0;
	};
}

#endif

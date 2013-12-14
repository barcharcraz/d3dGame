#pragma once
#include "stdafx.h"
#include <LibInput/Keys.h>
#include <LibInput/Input.h>
#include <windowing/IWindow.h>
namespace windows {
    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
    int Run();

    class Window : public windowing::IMultiWindow {
        friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
    public:
        Window();
        Window(int w, int h);
        virtual ~Window();
        HWND Hwnd();
        virtual void* Handle() override;
        virtual void Show() override;
        virtual void AttachInput(Input::Input* input) override;
        virtual void Present() override;
        virtual void Clear() override;
        virtual void MakeGLActive() override;
        virtual void MakeGLInactive() override;
        virtual void SetPresentOverride(std::function<void()> present) override;
        virtual void SetClearOverride(std::function<void()> clear) override;
        void ClearInput();
        void Update();
        std::function<void(Input::Keys)> onKeyDown;
        std::function<void(Input::Keys)> onKeyUp;
        std::function<void(long dx, long dy)> onMouseMove;
        std::function<void()> update;
    private:
        void init(int w, int h);
        void initDefault();
        void initRawInput();
        int handleRaw(HRAWINPUT raw);
        std::function<void()> m_presentOverride;
        std::function<void()> m_clearOverride;
        WNDCLASSEX _class;
        HWND _hwnd;
        HDC _dc;
        HGLRC _glctx;
        Input::Input* _input;
    };
    

}
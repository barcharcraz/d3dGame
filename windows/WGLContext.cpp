#include "stdafx.h"
#include "WGLContext.h"
#include <Utils/exceptions.h>
namespace windows {
    typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
    HGLRC WinGLCreateInitialContext(HDC wnd) {
        HGLRC rv = nullptr;
        PIXELFORMATDESCRIPTOR pfd;
        //zero initializ the pfd
        memset(&pfd, 0, sizeof(pfd));
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 24;
        pfd.cStencilBits = 8;
        pfd.iLayerType = PFD_MAIN_PLANE;
        int pixelNum = 0;
        pixelNum = ChoosePixelFormat(wnd, &pfd);
        if (0 == pixelNum) {
            throw utils::graphics_api_error("unsupported pixel format");
        }
        BOOL pixelStatus = FALSE;
        pixelStatus = SetPixelFormat(wnd, pixelNum, &pfd);
        if (FALSE == pixelStatus) {
            throw std::system_error(GetLastError(), std::system_category());
        }
        rv = wglCreateContext(wnd);
        if (nullptr == rv) {
            throw std::system_error(GetLastError(), std::system_category());
        }
        return rv;
    }
    HGLRC WinGLCreateContext(HDC wnd) {
        HGLRC temp = WinGLCreateInitialContext(wnd);
        BOOL wglCurrentResult = wglMakeCurrent(wnd, temp);
        if (FALSE == wglCurrentResult) {
            wglMakeCurrent(wnd, nullptr);
            wglDeleteContext(temp);
            throw std::system_error(GetLastError(), std::system_category());
        }
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("WGL_ARB_create_context");
        if (nullptr == wglCreateContextAttribsARB) {
            wglMakeCurrent(wnd, nullptr);
            wglDeleteContext(temp);
            throw std::system_error(GetLastError(), std::system_category());
        }
    }
}
#include "stdafx.h"
#include "WGLContext.h"
#include <Utils/exceptions.h>
#include <gl/GL.h>
namespace windows {
    typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB 0x2093
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_DEBUG_BIT_ARB 0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

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
        HGLRC rv = nullptr;
        HGLRC temp = WinGLCreateInitialContext(wnd);
        BOOL wglCurrentResult = wglMakeCurrent(wnd, temp);
        if (FALSE == wglCurrentResult) {
            wglMakeCurrent(wnd, nullptr);
            wglDeleteContext(temp);
            throw std::system_error(GetLastError(), std::system_category());
        }
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
        if (nullptr == wglCreateContextAttribsARB) {
            wglMakeCurrent(wnd, nullptr);
            wglDeleteContext(temp);
            throw std::system_error(GetLastError(), std::system_category());
        }
        const int attriblist [] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 1,
            0 //end
        };
        rv = wglCreateContextAttribsARB(wnd, nullptr, attriblist);
        if (nullptr == rv) {
            wglMakeCurrent(wnd, nullptr);
            wglDeleteContext(temp);
            wglDeleteContext(rv);
            throw std::system_error(GetLastError(), std::system_category());
        }
        wglMakeCurrent(wnd, nullptr);
        wglDeleteContext(temp);
        return rv;
    }
}
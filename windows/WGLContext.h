#pragma once
#include "stdafx.h"
namespace windows {
    /*! \brief creates an initial GL context using
    *          wglCreateContext and a PFD structure
    *          requests a 32bpp double buffered and
    *          hardware accelerated context. There is
    *          no way to get anything else
    */
    HGLRC WinGLCreateInitialContext(HDC wnd);
    HGLRC WinGLCreateContext(HDC wnd);
}
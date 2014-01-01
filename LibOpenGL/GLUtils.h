#ifndef LIBOPENGL_GLUTILS_H
#define LIBOPENGL_GLUTILS_H
#include "stdafx.h"
namespace LibOpenGL {
    //throws a graphics_api_error on an exception
    void CheckError();
    //converts a glenum to a string I should
    //not have to write this function
    const char* EnumString(GLenum val);

    
    
}

#endif

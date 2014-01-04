#ifndef RENDERINGUTILS_TEXTUREFUNCTIONS_H
#define RENDERINGUTILS_TEXTUREFUNCTIONS_H
#include <vector>
namespace utils {
    namespace tex {
        enum texture_type_e {
            TEXTURE2D,
            TEXTURE2D_CUBEMAP
        };
        //these values are the same
        //as those from both directX
        //and openGL
        enum cubemap_face_e {
            PLUS_X = 0,
            MINUX_X,
            PLUS_Y,
            MINUX_Y,
            PLUS_Z,
            MINUS_Z,
            MAX_SIDES
        };

        int numTexArrays(texture_type_e textype);
        int cubemapSquareWidth(int full_tex_width);
        int cubemapSquareSize(int full_tex_width);
        int cubemapSquareOffset(cubemap_face_e face, int full_tex_size);
        int texGetWidth(texture_type_e textype, int sourcewidth);
        int texGetHeight(texture_type_e textype, int sourceheight);
    }
}

#endif
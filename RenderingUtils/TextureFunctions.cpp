#include "TextureFunctions.h"
#include <Utils/exceptions.h>
namespace utils {
    namespace tex {
        int numTexArrays(texture_type_e textype) {
            switch (textype) {
            case utils::tex::TEXTURE2D:
                return 1;
            case utils::tex::TEXTURE2D_CUBEMAP:
                return 6;
            default:
                throw utils::invalid_enum_error("texture_type_e invalid");
            }
        }
        int cubemapSquareWidth(int full_tex_width) {
            return full_tex_width / 3;
        }
        int cubemapSquareSize(int full_tex_width) {
            int width = cubemapSquareWidth(full_tex_width);
            return width * width;
        }
        int cubemapSquareOffset(cubemap_face_e face, int full_tex_size) {
            //there are 6 faces, this operation
            //sets row = 0 if face is [0,2] and row=1 if
            //face is [3,5]
            int row = (face * 2) / 6;
            int squareSize = cubemapSquareSize(full_tex_size);
            int rowSize = squareSize * 3;
            int rowoffset = row * rowSize;
            //the position within its row that the face in question
            //is on, so face 5 would be at position 2 on row 1
            int faceOnRow = face % 3;
            int faceoffset = faceOnRow * cubemapSquareWidth(full_tex_size);
            return rowoffset + faceoffset;
        }
    }
}
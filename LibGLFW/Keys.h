#ifndef LIBGLFW_KEYS_H
#define LIBGLFW_KEYS_H
#include <unordered_map>
#include <LibInput/Keys.h>

namespace LibGLFW {
    extern std::unordered_map<int, Input::Keys> glfw_keymap;

}
#endif

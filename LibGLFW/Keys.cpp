#include "Keys.h"
#include <GLFW/glfw3.h>
namespace LibGLFW {
    std::unordered_map<int, Input::Keys> glfw_keymap = {
        { GLFW_KEY_UNKNOWN, Input::UNKNOWN },
        { GLFW_KEY_SPACE, Input::Space },
		{ GLFW_KEY_UP, Input::Up },
		{ GLFW_KEY_DOWN, Input::Down },
		{ GLFW_KEY_LEFT, Input::Left },
		{ GLFW_KEY_RIGHT, Input::Right },
        { GLFW_KEY_0, Input::Num0 },
        { GLFW_KEY_1, Input::Num1 },
        { GLFW_KEY_2, Input::Num2 },
        { GLFW_KEY_3, Input::Num3 },
        { GLFW_KEY_4, Input::Num4 },
        { GLFW_KEY_5, Input::Num5 },
        { GLFW_KEY_6, Input::Num6 },
        { GLFW_KEY_7, Input::Num7 },
        { GLFW_KEY_8, Input::Num8 },
        { GLFW_KEY_9, Input::Num9 },
        { GLFW_KEY_A, Input::A },
        { GLFW_KEY_B, Input::B },
        { GLFW_KEY_C, Input::C },
        { GLFW_KEY_D, Input::D },
        { GLFW_KEY_E, Input::E },
        { GLFW_KEY_F, Input::F },
        { GLFW_KEY_G, Input::G },
        { GLFW_KEY_H, Input::H },
        { GLFW_KEY_I, Input::I },
        { GLFW_KEY_J, Input::J },
        { GLFW_KEY_K, Input::K },
        { GLFW_KEY_L, Input::L },
        { GLFW_KEY_M, Input::M },
        { GLFW_KEY_N, Input::N },
        { GLFW_KEY_O, Input::O },
        { GLFW_KEY_P, Input::P },
        { GLFW_KEY_Q, Input::Q },
        { GLFW_KEY_R, Input::R },
        { GLFW_KEY_S, Input::S },
        { GLFW_KEY_T, Input::T },
        { GLFW_KEY_U, Input::U },
        { GLFW_KEY_V, Input::V },
        { GLFW_KEY_W, Input::W },
        { GLFW_KEY_X, Input::X },
        { GLFW_KEY_Y, Input::Y },
        { GLFW_KEY_Z, Input::Z }
    };
}

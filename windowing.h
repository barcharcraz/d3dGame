#include "config.h"
#include "windowing/IWindow.h"
#ifdef USE_GLFW
#include "LibGLFW/Window.h"

namespace windowing {
    using LibGLFW::Window;
    using LibGLFW::Run;
}
#elif defined USE_WIN32
#include "windows/Window.h"
#include "windows/Keys.h"
#include "windows/WinMain.h"
#include "windows/ComUtils.h"
namespace windowing {
    using windows::Window;
    using windows::Run;
}
#elif defined HAS_X11
#include "LibXWindows/Window.h"
namespace windowing = xwindows;
#endif


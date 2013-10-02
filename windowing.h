#include "config.h"

#ifdef GLFW3_FOUND
#include "LibGLFW/Window.h"
namespace windowing = LibGLFW;
#elif defined HAS_WIN32
#include "windows/Window.h"
#include "windows/Keys.h"
#include "windows/WinMain.h"
#include "windows/ComUtils.h"
namespace windowing = windows;
#elif defined HAS_X11
#include "LibXWindows/Window.h"
namespace windowing = xwindows;
#endif


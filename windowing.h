#include "config.h"
#ifdef HAS_WIN32
#include "windows/Window.h"
#include "windows/Keys.h"
#include "windows/WinMain.h"
#include "windows/ComUtils.h"
#endif
#ifdef HAS_X11
#include "LibXWindows/Window.h"
#endif


#ifdef HAS_WIN32
namespace windowing = windows;
#endif
#ifdef HAS_X11
namespace windowing = xwindows;
#endif

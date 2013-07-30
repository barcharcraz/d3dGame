set(libxwindows_files
        Window.h
        Window.cpp
        stdafx.h
        stdafx.cpp
)
find_package(X11)
add_library(LibXWindows STATIC ${libxwindows_files})
target_link_libraries(LibXWindows ${X11_LIBRARIES})

project (d3dgame)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(Eigen3 REQUIRED)
find_package(GLFW3)
find_package(OpenGL)
include_directories(${EIGEN3_INCLUDE_DIR} ${PROJECT_SOURCE_DIR} ${GLFW3_INCLUDE_PATH})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
IF(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-std=c++11)
ENDIF(CMAKE_COMPILER_IS_GNUCXX)
IF(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    add_definitions(-std=c++11 -Wall)
ENDIF()

#config.h configuration
INCLUDE(CheckIncludeFiles)
INCLUDE(CheckCXXSourceCompiles)
CHECK_INCLUDE_FILES(X11/Xlib.h HAS_X11)
CHECK_INCLUDE_FILES(windows.h HAS_WIN32)
CHECK_INCLUDE_FILES(GL/gl.h HAS_GL)
CHECK_INCLUDE_FILES(GL/glx.h HAS_GLX)
CHECK_INCLUDE_FILES(OpenGL/gl.h HAS_OPENGL) #screw you OSX

#check for make_unique
CHECK_CXX_SOURCE_COMPILES(
"
#include <memory>
int main() {
	int foo = std::make_unique<int>(4);
}
" HAS_MAKE_UNIQUE)


CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)
IF(WIN32)
add_definitions(-DUINCODE -D_UNICODE /W4)
set(CMAKE_EXE_LINKER_FLAGS /ENTRY:"wWinMainCRTStartup")
ENDIF(WIN32)
IF(APPLE)
	set(CMAKE_EXE_LINKER_FLAGS "-framework OpenGL -framework IOKit -framework Cocoa")
ENDIF(APPLE)
add_custom_target(Glue SOURCES windowing.h)

add_subdirectory(LibCommon)
add_subdirectory(assets)
add_subdirectory(Utils)
add_subdirectory(LibComponents)

add_subdirectory(LibOpenGL)
add_subdirectory(LibInput)
add_subdirectory(LibSystems)
add_subdirectory(LibImage)
add_subdirectory(LibPrefabs)
add_subdirectory(LibEffects)
IF(WIN32)
add_subdirectory(LibHLSL)
add_subdirectory(HLSLShaders)
add_subdirectory(LibDirect3D)
add_subdirectory(LibDirect2D)
add_subdirectory(LibDXGI)
add_subdirectory(windows)
add_subdirectory(SimpleEditor)
ENDIF(WIN32)
IF(HAS_X11)
add_subdirectory(LibXWindows)
ENDIF(HAS_X11)
IF(HAS_GLX)
add_subdirectory(LibGLX)
ENDIF(HAS_GLX)
IF(GLFW3_FOUND)
add_subdirectory(LibGLFW)
ENDIF(GLFW3_FOUND)
add_subdirectory(CrossplatApp)



#include <config.h>

#include <GL/glew.h>
#ifdef 	GLFW3_FOUND
#include <GLFW/glfw3.h>
#elif defined HAS_GL
#include <GL/gl.h>
#elif defined HAS_OPENGL
#include <OpenGL/gl.h>
#endif


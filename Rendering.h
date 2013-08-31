//! \brief includes renderers for the
//! current platform and typedefs some
//! default rendering types.
//!
//! \note this class MUST be #included before
//! windowing.h and libraries like GLUT and GLFW
//! this is because glLoadGen headers enforce this
//! for compatibility

#include "config.h"
#ifdef USE_OPENGL
#include "LibOpenGL/OpenGLRenderer.h"
#include "LibOpenGL/GLModelRenderer.h"
#endif

#ifndef GLUE_RENDERING_H
#define GLUE_RENDERING_H
namespace Rendering {
#ifdef USE_OPENGL
	typedef LibOpenGL::OpenGLRenderer Renderer;
	typedef LibOpenGL::GLModelRenderer ModelRenderer;
#endif
}
#endif
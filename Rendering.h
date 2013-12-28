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
#include "LibOpenGL/GLBillboardRenderer.h"
#elif defined USE_DIRECT3D
#include "LibDirect3D/Direct3DRenderer.h"
#include "LibDirect3D/ModelRenderer.h"
#include "LibDirect3D/BillboardRenderer.h"
#endif

#ifndef GLUE_RENDERING_H
#define GLUE_RENDERING_H
namespace Rendering {
#ifdef USE_OPENGL
	typedef LibOpenGL::OpenGLRenderer Renderer;
	typedef LibOpenGL::GLModelRenderer ModelRenderer;
	typedef LibOpenGL::GLBillboardRenderer BillboardRenderer;
#elif defined USE_DIRECT3D
	typedef LibDirect3D::Direct3DRenderer Renderer;
	typedef LibDirect3D::ModelRenderer ModelRenderer;
	typedef LibDirect3D::BillboardRenderer BillboardRenderer;
#endif
}
#endif
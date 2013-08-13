#ifndef LIBCOMPONENTS_TEXTURE_H
#define LIBCOMPONENTS_TEXTURE_H
#include "IComponent.h"
#include <LibImage/image.h>
namespace LibDirect3D {
	class Direct3DTexture;
}
namespace LibOpenGL {
	class OpenGLTexture;
}
namespace Components {
	class Texture : public IComponent {
	public:
		Texture(LibDirect3D::Direct3DTexture* d3dTex);
		LibDirect3D::Direct3DTexture* D3DTex();
	private:
		LibDirect3D::Direct3DTexture* _d3dTex;
		LibOpenGL::OpenGLTexture* _oglTex;
	};
}

#endif
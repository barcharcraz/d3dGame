#include "Texture.h"
#include <stdexcept>
namespace Components {
	Texture::Texture(Image::ImageData data)
		: _imageData(std::move(data))
	{
		
	}
	Texture::Texture(LibDirect3D::Direct3DTexture* d3dTex)
		: _d3dTex(d3dTex)
	{
	}
	LibDirect3D::Direct3DTexture* Texture::D3DTex() {
		if (_d3dTex == nullptr) {
			throw std::logic_error("Tried to ge a Direct3D texture from a component that does \
								   								   not have one");
		}
		return _d3dTex;
	}
	
	
}
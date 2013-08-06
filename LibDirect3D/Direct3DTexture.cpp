#include "stdafx.h"
#include "Direct3DTexture.h"
#include <LibImage/image.h>
namespace LibDirect3D {
	Direct3DTexture::Direct3DTexture(const Image::ImageData& data)
		: _data(data)
	{

	}
	//-------PRIVATE-----------
	void Direct3DTexture::initTexture(CComPtr<ID3D11Device> pDev) {

	}
}
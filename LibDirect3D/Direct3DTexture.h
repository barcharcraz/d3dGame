#pragma once
#include "stdafx.h"

namespace Image {
	struct ImageData;
}
namespace LibDirect3D {
	class Direct3DTexture {
	public:
		Direct3DTexture(const Image::ImageData& data);
		
	private:
		void initTexture(CComPtr<ID3D11Device> pDev);
		CComPtr<ID3D11Texture2D> _texture;
		CComPtr<ID3D11ShaderResourceView> _textureView;
		Image::ImageData _data;
	};
}
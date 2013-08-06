#pragma once
#include <Eigen/Core>
#include <DirectXMath.h>
#include <dxgiformat.h>
#include <d3d11.h>
#include <LibImage/image.h>
#include <map>
#include <vector>
namespace LibDirect3D {
	struct VertexData {
		Eigen::Vector3f Pos;
	};
	struct VSConstantBuffer {
		Eigen::Matrix4f worldViewProj;
	};
	const std::vector<D3D11_INPUT_ELEMENT_DESC> defaultLayout = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};


	const unsigned int defaultNumFeatureLevels = 7;
	const D3D_FEATURE_LEVEL defaultFeatureLevels[defaultNumFeatureLevels] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	std::map<Image::Formats, DXGI_FORMAT> DXGIFormats = {
		{Image::Formats::R8B8G8_UNORM, DXGI_FORMAT_UNKNOWN},
		{Image::Formats::R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM}
	};
}
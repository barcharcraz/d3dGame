#pragma once
#include <Eigen/Core>
#include <DirectXMath.h>
namespace LibDirect3D {
	struct VertexData {
		Eigen::Vector3f Pos;
	};

	const std::vector<D3D11_INPUT_ELEMENT_DESC> defaultLayout = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
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
}
#pragma once
#include <Eigen/Core>
#include <DirectXMath.h>
namespace LibDirect3D {
	struct VertexData {
		Eigen::Vector3f Pos;
	};

	D3D11_INPUT_ELEMENT_DESC defaultLayout [] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
}
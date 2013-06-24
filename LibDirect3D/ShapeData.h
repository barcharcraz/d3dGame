#pragma once
#include "stdafx.h"
#include "DataFormats.h"

namespace LibDirect3D {
	class InputData {
	public:

	private:
		std::vector<ID3D11Buffer> _vertexBuffers;
		std::vector<ID3D11Buffer> _indexBuffers;
		std::vector<unsigned int> _strides;
		std::vector<unsigned int> _offsets;
	};
}
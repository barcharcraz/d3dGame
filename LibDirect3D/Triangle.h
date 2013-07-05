#pragma once
#include "stdafx.h"
#include <LibCommon/IComponent.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "DataFormats.h"
#include "Direct3DRenderingMessage.h"

namespace LibDirect3D {
	class Triangle : public LibCommon::IComponent {
	public:
		Triangle();
	private:
		void init();

		void handleDraw(Direct3DRenderingMessage * msg);

		shaderSet _pActiveShaders;
		CComPtr<ID3D11Buffer> _pConstantBuffer;
		CComPtr<ID3D11Buffer> _pVertexBuffer;
		CComPtr<ID3D11Buffer> _pIndexBuffer;
		Eigen::Affine3f camera;
		std::vector<unsigned int> indices;
		std::vector<VertexData> verts;

	};
}
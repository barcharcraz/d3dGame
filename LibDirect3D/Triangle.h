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
		void initVertexBuffer(ID3D11Device1 * dev);
		void initIndexBuffer(ID3D11Device1 * dev);

		void handleDraw(Direct3DRenderingMessage * msg);

		shaderSet _pActiveShaders;
		CComPtr<ID3D11Buffer> _pVertexBuffer;
		CComPtr<ID3D11Buffer> _pIndexBuffer;
		unsigned int indices[3];
		VertexData verts[3];

	};
}
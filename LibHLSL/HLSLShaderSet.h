#pragma once
#include "stdafx.h"
#include <memory>
#include "HLSLVertexShader.h"
#include "HLSLPixelShader.h"
namespace LibShaders {
	struct HLSLShaderSet {
		HLSLShaderSet(const HLSLVertexShader& verts, const HLSLPixelShader& pixels)
			: vs(verts), ps(pixels) {}
		HLSLVertexShader vs;
		HLSLPixelShader ps;
	};
}

#pragma once
#include "stdafx.h"
#include <memory>
#include "HLSLVertexShader.h"
#include "HLSLPixelShader.h"
namespace LibShaders {
	struct HLSLShaderSet {
		HLSLPixelShader ps;
		HLSLVertexShader vs;
	};
}

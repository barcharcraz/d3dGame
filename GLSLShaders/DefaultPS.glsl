#version 130
#include "LightStructs.glslh"
out vec4 outputColor;
uniform directionalLight_t dlights[NUM_DIRECTIONAL];
uniform pointLight_t plights[NUM_POINT];
uniform material_t mat;
void main() {
  outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  
}

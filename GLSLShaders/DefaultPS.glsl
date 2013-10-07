#version 130
#include "LightStructs.glslh"
in vec4 normal;
out vec4 outputColor;
//uniform directionalLight_t dlights[NUM_DIRECTIONAL];
//uniform pointLight_t plights[NUM_POINT];
uniform material_t mat;
void main() {
  outputColor = normal;
  
}

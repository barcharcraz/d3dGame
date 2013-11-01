#version 130
#include "LightStructs.glslh"
in vec4 normal;
int vec4 uvOut;
out vec4 outputColor;
uniform directionalLight_t dlights[NUM_DIRECTIONAL];
uniform pointLight_t plights[NUM_POINT];
uniform material_t mat;
uniform usampler2D tex;
void main() {
  outputColor = texture(tex, uvOut);
  
}

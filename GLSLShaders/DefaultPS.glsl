#version 140
#pragma debug(on)
#include "LightStructs.glslh"
#include "ForwardLighting.glslh"
in vec4 normal;
in vec4 viewPos;
in vec3 uvout;
out vec4 outputColor;
layout(std140) uniform dirLightBlock {
	directionalLight_t dlights[NUM_DIRECTIONAL];
    //int numdlights;
};

layout(std140) uniform pointLightBlock {
	pointLight_t plights[NUM_POINT];
    //int numdlights;
};

uniform material_t mat;
uniform sampler2D tex;
void main() {
    outputColor = mat.ambiant;
    for(int i = 0; i < NUM_POINT; ++i) {
        outputColor += pointLight(plights[i], normal, viewPos, mat); 
    }
    for(int i = 0; i < NUM_DIRECTIONAL; ++i) {
        outputColor += directionalLight(dlights[i], normal, viewPos, mat); 
    }
    outputColor = clamp(outputColor, 0.0, 1.0);
    outputColor = outputColor + texture(tex, uvout.xy);
	outputColor.x = dlights[0].diffuse.x;
  
}

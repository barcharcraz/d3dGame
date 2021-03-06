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
};
uniform material_t mat;
uniform sampler2D tex;
void main() {
    outputColor = mat.ambiant;
    //for(int i = 0; i < NUM_POINT; ++i) {
    //    outputColor += pointLight(plights[i], normal, viewPos * -1, mat);
    //}
    for(int i = 0; i < NUM_DIRECTIONAL; ++i) {
        outputColor += directionalLight(dlights[i], normal, viewPos, mat); 
    } 
    outputColor = clamp(outputColor, 0.0, 1.0);
    outputColor = outputColor * texture(tex, vec2(uvout.x, 1 - uvout.y));
    //outputColor.x = dot(normalize(dlights[0].direction), normalize(normal)); 
    //outputColor.y = 0;
    //outputColor.z = 0;
    //outputColor.xyz = normalize(-normal).xyz; 
}

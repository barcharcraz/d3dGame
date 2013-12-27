#version 140
in vec3 uvout;
out vec4 outputColor;
uniform sampler3D tex;
void main() {
	outputColor = texture(tex, uvout.xy);
}
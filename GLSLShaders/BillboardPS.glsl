#version 140
in vec3 uvout;
out vec4 outputColor;
uniform sampler2D tex;
void main() {
	outputColor = texture(tex, uvout.xy);
	if(outputColor.a > 0.5) {
		discard;
	}
}
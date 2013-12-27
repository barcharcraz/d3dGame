#version 140

struct matrices_t {
	mat4 model;
	mat4 view;
	mat4 proj;
};
uniform matrices_t mvp;
in vec4 pos;
in vec4 norm;
in vec4 uv;
out vec3 uvout;
void main() {
	mat4 concatmat = mvp.proj * mvp.view * mvp.model;
	uvout = uv.xyz;
	gl_position = concatmat * pos;
}
#version 140

struct matrices_t {
    mat4 model;
    mat4 view;
    mat4 proj;
};
uniform matrices_t mvp;
uniform mat4 normTrans;

in vec4 pos;
in vec4 norm;
in vec3 uv;
out vec4 normal;
out vec4 viewPos;
out vec3 uvout;
void main() {
	uvout = uv;
	vec4 rv = mvp.model * pos;
	rv = mvp.view * rv;
    viewPos = rv;
	rv = mvp.proj * rv;
	mat4 modelView = mvp.model * mvp.view;
	normal.xyz = mat3(modelView) * norm.xyz;
	normal.w = float(1);
	normal = normTrans * normal;
	gl_Position = rv;
}

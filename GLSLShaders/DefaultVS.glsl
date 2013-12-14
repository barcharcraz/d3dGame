#version 140

struct matrices_t {
    mat4 model;
    mat4 view;
    mat4 proj;
};
uniform matrices_t mvp;
uniform mat3 normTrans;

in vec4 pos;
in vec4 norm;
in vec3 uv;
out vec4 normal;
out vec4 viewPos;
out vec3 uvout;
void main() {
	uvout = uv;
	mat4 modelviewproj = mvp.proj * mvp.view * mvp.model;
	mat4 modelview =  mvp.view * mvp.model;
	
	vec4 rv = modelviewproj * pos;
	viewPos = modelview * pos;
	
	normal.xyz = mat3(modelview) * norm.xyz;
	normal.w = float(0);
	gl_Position = rv;
}

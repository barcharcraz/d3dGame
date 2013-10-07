#version 130
in vec4 pos;
in vec4 norm;
in vec3 uv;
out vec4 normal;
struct matrices_t {
    mat4 model;
    mat4 view;
    mat4 proj;
};
uniform matrices_t mvp;
uniform mat4 normTrans;
void main() {
  vec4 rv = mvp.model * pos;
  rv = mvp.view * rv;
  rv = mvp.proj * rv;
  normal.xyz = mat3(mvp.model * mvp.view) * norm.xyz;
  normal.w = 1;
  normal = normTrans * normal;
  gl_Position = rv;
}

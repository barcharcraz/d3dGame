#version 130
layout(location=0) in vec4 pos;
layout(location=1) in vec4 norm;
layout(location=2) in vec3 uv;
struct matrices_t {
    mat4 model;
    mat4 view;
    mat4 proj;
};
uniform matrices_t mvp;
void main() {
  vec4 rv = mvp.model * pos;
  rv = mvp.view * rv;
  rv = mvp.proj * rv;
  gl_Position = rv;
}

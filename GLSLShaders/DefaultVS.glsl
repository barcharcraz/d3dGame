#version 130
in vec4 pos;
in vec4 norm;
in vec3 uv;

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

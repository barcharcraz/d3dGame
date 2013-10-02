#version 130
in vec4 pos;
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

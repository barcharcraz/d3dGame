#version 130
in vec4 pos;
struct matrices_t {
    mat4 model;
    mat4 view;
    mat4 proj;
};
uniform matrices_t mvp;
void main() {
  vec4 rv = pos * mvp.model;
  rv = rv * mvp.view;
  rv = rv * mvp.proj;
  gl_Position = rv;
}

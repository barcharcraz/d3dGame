#version 130
in vec4 pos;
uniform matrices_t {
    mat4 model;
    mat4 view;
    mat4 proj;
};
void main() {
  vec4 rv = pos * model;
  rv = rv * view;
  rv = rv * proj;
  gl_Position = rv;
}

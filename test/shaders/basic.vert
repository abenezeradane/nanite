#version 330 core
layout (location = 0) in vec3 initial;
uniform vec3 position;
void main() {
   gl_Position = vec4(initial + position, 1.0);
}
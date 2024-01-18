#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

uniform mat4 model;
uniform mat4 view;

out vec3 color;

void main() {
    gl_Position = view * model * vec4(inPosition, 1.0);
    color = inColor;
}

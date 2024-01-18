#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 cameraPosition;  // New uniform for camera position

in vec3 inPosition;  // Vertex position

out vec3 fragPosition;  // Pass position to fragment shader

void main() {
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
    fragPosition = vec3(model * vec4(inPosition, 1.0));  // Transform vertex position to world space
}

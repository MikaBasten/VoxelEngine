#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragColor;
out float depth; // Add this line

void main() {
    // Combine matrices to get the final MVP (Model-View-Projection) matrix
    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(inPosition, 1.0);

    // Pass color to fragment shader
    fragColor = inColor;

    // Calculate depth for the fragment
    depth = gl_Position.z / gl_Position.w;
}

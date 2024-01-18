#version 330 core

in vec3 fragColor;
in float depth; // Add this line

out vec4 finalColor;

void main() {
    // Use depth value for coloring (you can customize this based on your requirements)
    vec3 colorFromDepth = vec3(depth);

    // Combine color from the vertex and depth-based color
    finalColor = vec4(fragColor * colorFromDepth, 1.0);
}

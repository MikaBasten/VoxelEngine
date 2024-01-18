#version 330 core

in vec3 fragPosition;  // Received from vertex shader

out vec4 FragColor;

void main() {
    vec3 cameraPosition = vec3(0.0, 0.0, 3.0);  // Set your camera position here
    float distanceToCamera = length(fragPosition - cameraPosition);

    // Use distanceToCamera for some color computation
    FragColor = vec4(vec3(distanceToCamera), 1.0);
}

#include "Camera.h"
#include <iostream>

Camera::Camera()
    : position(glm::vec3(0.0f, 0.0f, 1.0f)),
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    up(glm::vec3(0.0f, 1.0f, 0.0f)),
    speed(0.05f),
    yaw(-90.0f),   // Initial yaw angle
    pitch(0.0f) {} // Initial pitch angle

Camera::~Camera() {
    // Destructor implementation...
}

void Camera::Update(SDL_Event& event) {
    std::cout << "Camera Position: (" << position.x << ", " << position.y << ", " << position.z << ", " << pitch << ", " << yaw << ")" << std::endl;
    switch (event.type) {
    case SDL_KEYDOWN:
        HandleKeyPress(event.key.keysym.sym);
        break;
    case SDL_KEYUP:
        HandleKeyRelease(event.key.keysym.sym);
        break;
    case SDL_MOUSEMOTION:
        HandleMouseMovement(event.motion.xrel, event.motion.yrel);
        break;
    default:
        break;
    }
}

void Camera::HandleKeyPress(SDL_Keycode key) {
    switch (key) {
    case SDLK_w:
        position += speed * front;
        break;
    case SDLK_s:
        position -= speed * front;
        break;
    case SDLK_a:
        position -= glm::normalize(glm::cross(front, up)) * speed;
        break;
    case SDLK_d:
        position += glm::normalize(glm::cross(front, up)) * speed;
        break;
    case SDLK_SPACE:
        position += speed * up;
        break;
    case SDLK_LCTRL:
        position -= speed * up;
        break;

    default:
        break;
    }
}

void Camera::HandleKeyRelease(SDL_Keycode key) {
    // Handle key release events if needed
}

void Camera::HandleMouseMovement(int deltaX, int deltaY) {
    // Adjust yaw and pitch based on mouse movement
    const float sensitivity = 0.2f;
    deltaX *= sensitivity;
    deltaY *= sensitivity;

    yaw += deltaX;
    pitch -= deltaY;

    // Clamp pitch to avoid flipping the camera
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    // Update the front vector based on yaw and pitch
    front.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    front.y = std::sin(glm::radians(pitch));
    front.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));

    // Normalize the front vector
    front = glm::normalize(front);
}
#pragma once

#include <SDL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(); 
    ~Camera();

    void Update(SDL_Event& event);

    glm::mat4 GetViewMatrix() const {
        return glm::lookAt(position, position + front, up);
    }

    void HandleMouseMovement(int deltaX, int deltaY);

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float speed;

    float yaw;   // Yaw angle (horizontal rotation)
    float pitch; // Pitch angle (vertical rotation)

    void HandleKeyPress(SDL_Keycode key);
    void HandleKeyRelease(SDL_Keycode key);
};
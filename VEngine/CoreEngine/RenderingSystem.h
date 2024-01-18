#include <iostream>
#include <vector>
#include <glew.h>
#include <SDL.h>
#include "ShaderLoader.h"  
#include "Camera.h"

class RenderingSystem {
public:
    RenderingSystem();
    ~RenderingSystem();

    void Initialize(int screenWidth, int screenHeight, bool fullscreen);
    void Render();
    void ResizeWindow(int newWidth, int newHeight);
    void ToggleFullscreen();
    void UpdateCamera(SDL_Event& event);
    // Inside Camera class
    glm::mat4 GetProjectionMatrix();


private:
    SDL_Window* window;
    SDL_GLContext context;
    GLuint vertexArrayID;
    GLuint vertexBufferID;
    GLuint shaderProgramID;  // Added for shader support
    int screenWidth;
    int screenHeight;
    bool isFullscreen;
    bool isMouseLocked;

    Camera camera;

    void SetupShaders();
};
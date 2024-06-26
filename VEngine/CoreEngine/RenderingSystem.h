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
    void LoadScene(const GLfloat* vertexBufferData, GLsizei vertexBufferSize, const GLuint* indexBufferData, GLsizei indexBufferSize);
    void Render(bool wireframeMode);
    void ResizeWindow(int newWidth, int newHeight);
    void ToggleFullscreen();
    void UpdateCamera(SDL_Event& event);
    // Inside Camera class
    glm::mat4 GetProjectionMatrix();


private:
    SDL_Window* window;
    SDL_GLContext context;
    GLsizei indexCount;
    GLuint vertexArrayID;
    GLuint vertexBufferID;
    GLuint elementBufferID;
    GLuint shaderProgramID;  // Added for shader support
    int screenWidth;
    int screenHeight;
    bool isFullscreen;
    bool isMouseLocked;

    Camera camera;

    void SetupShaders();
};
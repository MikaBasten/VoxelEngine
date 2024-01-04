#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <glew.h>

class RenderingSystem {
public:
    RenderingSystem();
    ~RenderingSystem();

    void Initialize(int screenWidth, int screenHeight, bool fullscreen);
    void Render();
    void ResizeWindow(int newWidth, int newHeight);
    void ToggleFullscreen();

private:
    SDL_Window* window;
    SDL_GLContext context;
    GLuint vertexArrayID;
    GLuint vertexBufferID;
    int screenWidth;
    int screenHeight;
    bool isFullscreen;

    // Add any additional OpenGL-related variables you need
};

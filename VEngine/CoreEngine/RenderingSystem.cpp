#include "RenderingSystem.h"
#include <iostream>

RenderingSystem::RenderingSystem()
    : window(nullptr), context(nullptr), vertexArrayID(0), vertexBufferID(0),
    screenWidth(800), screenHeight(600), isFullscreen(false) {}

RenderingSystem::~RenderingSystem() {
    // Cleanup code for SDL and OpenGL resources
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteVertexArrays(1, &vertexArrayID);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void RenderingSystem::Initialize(int screenWidth, int screenHeight, bool fullscreen) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->isFullscreen = fullscreen;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        // Handle initialization failure (throw an exception, exit the program, etc.)
    }

    // Create SDL window
    Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    if (fullscreen) {
        windowFlags |= SDL_WINDOW_FULLSCREEN;
    }

    window = SDL_CreateWindow(
        "Game Engine",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        screenWidth,
        screenHeight,
        windowFlags
    );

    if (window == nullptr) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        // Handle window creation failure (throw an exception, exit the program, etc.)
    }

    // Create OpenGL context
    context = SDL_GL_CreateContext(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed" << std::endl;
        // Handle GLEW initialization failure (throw an exception, exit the program, etc.)
    }

    // Set the clear color to, for example, white (R, G, B, A)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


    // Display OpenGL and GLEW information
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;

    // Set up OpenGL states, shaders, etc.

    // Generate and bind a Vertex Array Object (VAO)
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Create a simple triangle for demonstration purposes
    GLfloat vertexBufferData[] = {
       -0.5f, -0.5f, 0.0f,  // Vertex 1: position (x, y, z)
        0.5f, -0.5f, 0.0f,  // Vertex 2: position (x, y, z)
        0.0f,  0.5f, 0.0f   // Vertex 3: position (x, y, z)
    };

    // Generate and bind a Vertex Buffer Object (VBO)
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
}

void RenderingSystem::Render() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Use a simple shader program (you need to set up shaders)
    // ...

    // Bind the Vertex Array Object (VAO)
    glBindVertexArray(vertexArrayID);

    // Enable the vertex attribute array
    glEnableVertexAttribArray(0);

    // Specify the format of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Disable the vertex attribute array
    glDisableVertexAttribArray(0);

    // Unbind the Vertex Array Object (VAO)
    glBindVertexArray(0);

    // Swap buffers at the end of the rendering process
    SDL_GL_SwapWindow(window);
}


void RenderingSystem::ResizeWindow(int newWidth, int newHeight) {
    screenWidth = newWidth;
    screenHeight = newHeight;
    SDL_SetWindowSize(window, newWidth, newHeight);
    // Additional code to handle resizing, if needed
}

void RenderingSystem::ToggleFullscreen() {
    isFullscreen = !isFullscreen;
    SDL_SetWindowFullscreen(window, isFullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    // Additional code to handle fullscreen toggle, if needed
}

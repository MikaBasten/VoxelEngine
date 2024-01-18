#include "RenderingSystem.h"
#include "ShaderLoader.h"
#include <iostream>
#include <filesystem>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

RenderingSystem::RenderingSystem()
    : window(nullptr), context(nullptr), vertexArrayID(0), vertexBufferID(0),
    shaderProgramID(0), screenWidth(800), screenHeight(600), isFullscreen(false) {}

RenderingSystem::~RenderingSystem() {
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteVertexArrays(1, &vertexArrayID);
    glDeleteProgram(shaderProgramID);  // Delete shader program
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
        // Vertex 1: position (x, y, z), color (r, g, b)
        -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Red

        // Vertex 2: position (x, y, z), color (r, g, b)
        1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Green

        // Vertex 3: position (x, y, z), color (r, g, b)
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f  // Blue

    };


    // Generate and bind a Vertex Buffer Object (VBO)
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

    // Initialize shaders
    SetupShaders();
}

void RenderingSystem::SetupShaders() {
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    // Load and compile shaders 
    GLuint vertexShaderID = LoadShader("vertex_shader.glsl", GL_VERTEX_SHADER);
    GLuint fragmentShaderID = LoadShader("fragment_shader.glsl", GL_FRAGMENT_SHADER);

    // Link shaders into a program
    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);

    // Check for linking errors
    GLint linkResult;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &linkResult);
    if (linkResult == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> programError(static_cast<size_t>(infoLogLength));
        glGetProgramInfoLog(shaderProgramID, infoLogLength, nullptr, programError.data());
        std::cerr << "Error linking shader program:\n" << programError.data() << std::endl;
        // Handle error (throw an exception, exit the program, etc.)
    }

    // Detach and delete the individual shaders (no longer needed after linking)
    glDetachShader(shaderProgramID, vertexShaderID);
    glDetachShader(shaderProgramID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    // Use the shader program
    glUseProgram(shaderProgramID);

    // Specify the format of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Get the uniform locations
    GLint modelMatrixLocation = glGetUniformLocation(shaderProgramID, "model");
    GLint viewMatrixLocation = glGetUniformLocation(shaderProgramID, "view");

    // Check for uniform location validity (you should handle this more gracefully)
    if (modelMatrixLocation == -1 || viewMatrixLocation == -1) {
        std::cerr << "Error: Could not get uniform locations." << std::endl;
        // Handle error (throw an exception, exit the program, etc.)
    }

    // Set the initial model matrix (identity matrix)
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void RenderingSystem::Render() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Configure viewport
    glViewport(0, 0, screenWidth, screenHeight);

    // Get the camera's view matrix
    glm::mat4 viewMatrix = camera.GetViewMatrix();

    // Set the view matrix uniform in the shader program
    GLint viewMatrixLocation = glGetUniformLocation(shaderProgramID, "view");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Set the model matrix to the identity matrix (no translation)
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    GLint modelMatrixLocation = glGetUniformLocation(shaderProgramID, "model");
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Draw the triangle using shaders
    glBindVertexArray(vertexArrayID);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap buffers at the end of the rendering process
    SDL_GL_SwapWindow(window);

    // Check for OpenGL errors after rendering
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error (after rendering): " << error << std::endl;
    }
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

void RenderingSystem::UpdateCamera(SDL_Event& event)
{
    camera.Update(event);
}

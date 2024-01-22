#include "RenderingSystem.h"
#include "ShaderLoader.h"
#include <iostream>
#include <filesystem>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

RenderingSystem::RenderingSystem()
    : window(nullptr), context(nullptr), vertexArrayID(0), vertexBufferID(0),
    shaderProgramID(0), screenWidth(800), screenHeight(600), isFullscreen(false), isMouseLocked(false) {}


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

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set the depth test function
    glDepthFunc(GL_LESS);

    // Set the clear color to, for example, white (R, G, B, A)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Display OpenGL and GLEW information
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;

    // Set up OpenGL states, shaders, etc.

    // Generate and bind a Vertex Array Object (VAO)
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Generate and bind a Vertex Buffer Object (VBO)
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

    // Generate and bind Element Buffer Object (EBO)
    glGenBuffers(1, &elementBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);

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
    GLint projectionMatrixLocation = glGetUniformLocation(shaderProgramID, "projection"); // Add this line

    // Check for uniform location validity (you should handle this more gracefully)
    if (modelMatrixLocation == -1 || viewMatrixLocation == -1 || projectionMatrixLocation == -1) {
        std::cerr << "Error: Could not get uniform locations." << std::endl;
        // Handle error (throw an exception, exit the program, etc.)
    }

    // Set the initial model matrix (identity matrix)
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Set up perspective projection matrix
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 100.0f);
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}


void RenderingSystem::LoadScene(const GLfloat* vertices, GLsizei verticesSize, const GLuint* indices, GLsizei indicesSize) {
    // Create Vertex Array Object (VAO)
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Create Vertex Buffer Object (VBO)
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    // Create Element Buffer Object (EBO)
    glGenBuffers(1, &elementBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    // Specify the layout of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Specify the color data
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Update the index count
    indexCount = indicesSize / sizeof(GLuint);
}




void RenderingSystem::Render(bool wireframeMode) {
    // Clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use the shader program
    glUseProgram(shaderProgramID);

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

    // Draw the geometry using shaders and EBO
    glBindVertexArray(vertexArrayID);

    // Set wireframe mode
    if (wireframeMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Draw the geometry using shaders and EBO
    glBindVertexArray(vertexArrayID);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

    // Reset to default polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

void RenderingSystem::UpdateCamera(SDL_Event& event) {
    // Handle mouse locking
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_l) {
        isMouseLocked = !isMouseLocked;
        SDL_SetRelativeMouseMode(isMouseLocked ? SDL_TRUE : SDL_FALSE);

        // If mouse is locked, warp it to the center of the screen
        if (isMouseLocked) {
            int centerX = screenWidth / 2;
            int centerY = screenHeight / 2;
            SDL_WarpMouseInWindow(window, centerX, centerY);
        }
    }

    // Update the camera with mouse movement
    int mouseX, mouseY;
    SDL_GetRelativeMouseState(&mouseX, &mouseY);
    camera.HandleMouseMovement(mouseX, mouseY);

    // Update the camera with other events (keyboard, etc.)
    camera.Update(event);
}

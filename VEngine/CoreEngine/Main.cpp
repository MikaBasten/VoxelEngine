#pragma once
#include "RenderingSystem.h"
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

int SDL_main(int argc, char* argv[]) {

    bool wireframeMode = false;
    RenderingSystem renderingSystem;


    renderingSystem.Initialize(800, 600, false);


    // Vertices for a square
    GLfloat squareVertices[] = {
        // Vertex 1: position (x, y, z), color (r, g, b)
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Top-left, Red

        // Vertex 2: position (x, y, z), color (r, g, b)
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Top-right, Green

         // Vertex 4: position (x, y, z), color (r, g, b)
          0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,   // Bottom-right, White

          // Vertex 3: position (x, y, z), color (r, g, b)
          -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // Bottom-left, Blue
    };

    GLuint squareIndices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLfloat triangleVertices[] = {
        // Vertex 1: position (x, y, z), color (r, g, b)
        -1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Top-left, Red

        // Vertex 2: position (x, y, z), color (r, g, b)
         1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Top-right, Green

         // Vertex 3: position (x, y, z), color (r, g, b)
          0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // Bottom-right, Blue

    };

    GLuint triangleIndices[] = {
        0, 1, 2
    };

    GLfloat cubeVertices[] = {
        // Vertex 0: position (x, y, z), color (r, g, b)
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Bottom-left-front, Red
        // Vertex 1: position (x, y, z), color (r, g, b)
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  // Bottom-right-front, Green
         // Vertex 2: position (x, y, z), color (r, g, b)
          0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  // Top-right-front, Blue
          // Vertex 3: position (x, y, z), color (r, g, b)
          -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // Top-left-front, White

          // Vertex 4: position (x, y, z), color (r, g, b)
          -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // Bottom-left-back, Red
          // Vertex 5: position (x, y, z), color (r, g, b)
           0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Bottom-right-back, Green
           // Vertex 6: position (x, y, z), color (r, g, b)
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // Top-right-back, Blue
            // Vertex 7: position (x, y, z), color (r, g, b)
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f   // Top-left-back, White
    };

    GLuint cubeIndices[] = {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Left face
        0, 3, 7,
        7, 4, 0,

        // Right face
        1, 5, 6,
        6, 2, 1,

        // Top face
        3, 2, 6,
        6, 7, 3,

        // Bottom face
        0, 1, 5,
        5, 4, 0
    };



    // Load the single polygon scene
    renderingSystem.LoadScene(squareVertices, sizeof(squareVertices), squareIndices, sizeof(squareIndices));


    // Main render loop
    bool isRunning = true;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_u) {
                renderingSystem.LoadScene(triangleVertices, sizeof(triangleVertices),
                    triangleIndices, sizeof(triangleIndices));
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_i) {
                renderingSystem.LoadScene(squareVertices, sizeof(squareVertices),
                    squareIndices, sizeof(squareIndices));
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_o) {
                renderingSystem.LoadScene(cubeVertices, sizeof(cubeVertices),
                    cubeIndices, sizeof(cubeIndices));
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) {
                wireframeMode = !wireframeMode;
            }
            // Pass the event to the camera for handling
            renderingSystem.UpdateCamera(event);
        }

        // You can call other update logic here

        renderingSystem.Render(36, wireframeMode);

        // You might want to add a delay to control the frame rate
        SDL_Delay(16); // Adjust as needed
    }

    return 0;
}
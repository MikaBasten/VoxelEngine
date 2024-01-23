#pragma once
#include "RenderingSystem.h"
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

int SDL_main(int argc, char* argv[]) {

    bool wireframeMode = false;
    bool cube = false;
    bool d20 = true;
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

    // These are the 12 vertices for the icosahedron
    GLfloat icosahedronVertices[] = {
        // Vertex 0: position (x, y, z), color (r, g, b)
        -0.525731112119133606f, 0.0f, 0.850650808352039932f, 1.0f, 0.0f, 0.0f,  // Red

        // Vertex 1: position (x, y, z), color (r, g, b)
        0.525731112119133606f, 0.0f, 0.850650808352039932f, 0.0f, 1.0f, 0.0f,  // Green

        // Vertex 2: position (x, y, z), color (r, g, b)
        -0.525731112119133606f, 0.0f, -0.850650808352039932f, 0.0f, 0.0f, 1.0f,  // Blue

        // Vertex 3: position (x, y, z), color (r, g, b)
        0.525731112119133606f, 0.0f, -0.850650808352039932f, 1.0f, 1.0f, 1.0f,  // White

        // Vertex 4: position (x, y, z), color (r, g, b)
        0.0f, 0.850651f, 0.525731f, 1.0f, 0.0f, 0.0f,  // Red

        // Vertex 5: position (x, y, z), color (r, g, b)
        0.0f, 0.850651f, -0.525731f, 0.0f, 1.0f, 0.0f,  // Green

        // Vertex 6: position (x, y, z), color (r, g, b)
        0.0f, -0.850651f, 0.525731f, 0.0f, 0.0f, 1.0f,  // Blue

        // Vertex 7: position (x, y, z), color (r, g, b)
        0.0f, -0.850651f, -0.525731f, 1.0f, 1.0f, 1.0f,  // White

        // Vertex 8: position (x, y, z), color (r, g, b)
        0.850651f, 0.525731f, 0.0f, 1.0f, 0.0f, 0.0f,  // Red

        // Vertex 9: position (x, y, z), color (r, g, b)
        -0.850651f, 0.525731f, 0.0f, 0.0f, 1.0f, 0.0f,  // Green

        // Vertex 10: position (x, y, z), color (r, g, b)
        0.850651f, -0.525731f, 0.0f, 0.0f, 0.0f, 1.0f,  // Blue

        // Vertex 11: position (x, y, z), color (r, g, b)
        -0.850651f, -0.525731f, 0.0f, 1.0f, 1.0f, 1.0f  // White
    };

    // Indices for triangles
    GLuint icosahedronIndices[] = {
       0,4,1,
        0,9,4,
        9,5,4,
        4,5,8,
        4,8,1,

        8,10,1,
        8,3,10,
        5,3,8,
        5,2,3,
        2,7,3,

        7,10,3,
        7,6,10,
        7,11,6,
        11,0,6,
        0,1,6,

        6,1,10,
        9,0,11,
        9,11,2,
        9,2,5,
        7,2,11
    };





    // Load the single polygon scene
    renderingSystem.LoadScene(icosahedronVertices, sizeof(icosahedronVertices), icosahedronIndices, sizeof(icosahedronIndices));

    
    // Main render loop
    bool isRunning = true;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_y) {
                cube = false;
                d20 = false;
                renderingSystem.LoadScene(triangleVertices, sizeof(triangleVertices),
                    triangleIndices, sizeof(triangleIndices));
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_u) {
                cube = false;
                d20 = false;
                renderingSystem.LoadScene(squareVertices, sizeof(squareVertices),
                    squareIndices, sizeof(squareIndices));
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_i) {
                d20 = false;
                cube = !cube;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_o) {
                cube = false;
                d20 = !d20;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) {
                wireframeMode = !wireframeMode;
            }
            // Pass the event to the camera for handling
            renderingSystem.UpdateCamera(event);
        }

        // Update logic for rotation
        float rotationSpeed = 0.005f; // Adjust as needed
        if (cube) {
            // Apply rotation to the cube vertices
            for (int i = 0; i < sizeof(cubeVertices) / sizeof(cubeVertices[0]); i += 6) {
                float x = cubeVertices[i];
                float z = cubeVertices[i + 2];

                cubeVertices[i] = x * cos(rotationSpeed) - z * sin(rotationSpeed);
                cubeVertices[i + 2] = x * sin(rotationSpeed) + z * cos(rotationSpeed);
            }
            renderingSystem.LoadScene(cubeVertices, sizeof(cubeVertices),
                cubeIndices, sizeof(cubeIndices));
        }
        if (d20) {
            // Apply rotation to the cube vertices
            for (int i = 0; i < sizeof(icosahedronVertices) / sizeof(icosahedronVertices[0]); i += 6) {
                float x = icosahedronVertices[i];
                float z = icosahedronVertices[i + 2];

                icosahedronVertices[i] = x * cos(rotationSpeed) - z * sin(rotationSpeed);
                icosahedronVertices[i + 2] = x * sin(rotationSpeed) + z * cos(rotationSpeed);
            }
            renderingSystem.LoadScene(icosahedronVertices, sizeof(icosahedronVertices),
                icosahedronIndices, sizeof(icosahedronIndices));
        }
        // You can call other update logic here
        renderingSystem.Render(wireframeMode);

        // You might want to add a delay to control the frame rate
        SDL_Delay(16); // Adjust as needed
    }

    return 0;
}
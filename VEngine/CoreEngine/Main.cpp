#pragma once
#include "RenderingSystem.h"
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

int SDL_main(int argc, char* argv[]) {
    RenderingSystem renderingSystem;

    renderingSystem.Initialize(800, 600, false);


    // Vertices for a square
    GLfloat squareVertices[] = {
        // Vertex 1: position (x, y, z), color (r, g, b)
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Top-left, Red

        // Vertex 2: position (x, y, z), color (r, g, b)
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Top-right, Green

         // Vertex 3: position (x, y, z), color (r, g, b)
          0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // Bottom-right, Blue

          // Vertex 4: position (x, y, z), color (r, g, b)
          -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f   // Bottom-left, White
    };


    // Load the single polygon scene
    renderingSystem.LoadScene(squareVertices, sizeof(squareVertices));


    // Main render loop
    bool isRunning = true;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }

            // Pass the event to the camera for handling
            renderingSystem.UpdateCamera(event);
        }

        // You can call other update logic here
        
        renderingSystem.Render(6);

        // You might want to add a delay to control the frame rate
        SDL_Delay(16); // Adjust as needed
    }

    return 0;
}
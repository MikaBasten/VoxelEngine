#pragma once
#include "RenderingSystem.h"
#include <iostream>


int main() {
    RenderingSystem renderingSystem;

    renderingSystem.Initialize(800, 600, false);

    // Main render loop
    bool isRunning = true;
    while (isRunning) {
        // Handle SDL events (e.g., user input)
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Render a frame
        renderingSystem.Render();

        // You might want to add a delay to control the frame rate
        SDL_Delay(16); // Adjust as needed
    }

    return 0;
}
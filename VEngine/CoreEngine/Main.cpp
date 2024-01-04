#pragma once
#include "RenderingSystem.h"
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

int SDL_main(int argc, char* argv[]) {
    RenderingSystem renderingSystem;

    renderingSystem.Initialize(800, 600, false);

    // Main render loop
    bool isRunning = true;
    while (isRunning) {

        renderingSystem.Render();;
        // You might want to add a delay to control the frame rate
        SDL_Delay(16); // Adjust as needed
    }

    return 0;
}
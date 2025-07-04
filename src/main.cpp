#include <iostream>
#include <SDL2/SDL.h>
#include "window.h"
#include "dot.h"
#include "inputHandler.h"
#include "gameplay.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

int main()
{
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "SDL2 Game");

    if (window.init() != 0)
    {
        std::cout << "Failed to initialize SDL!" << std::endl;
        return 1;
    }

    if (window.create() != 0)
    {
        std::cout << "Failed to create window!" << std::endl;
        return 1;
    }

    // Create gameplay manager
    Gameplay gameplay(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create input handler
    InputHandler inputHandler;

    // Set up gameplay input callbacks
    gameplay.setupInputCallbacks(inputHandler);
    Uint32 frameStart;
    int frameTime;

    // Game loop
    while (gameplay.isRunning())
    {
        frameStart = SDL_GetTicks();

        // Handle events
        inputHandler.pollEvents();

        // Update game state
        gameplay.update();

        // Render
        window.renderBackground(0, 0, 0); // Black background
        gameplay.render(window.getRenderer());
        window.present();

        // Frame rate limiting
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
        {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    std::cout << "Game ended successfully!" << std::endl;
    return 0;
}
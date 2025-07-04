#include <iostream>
#include <SDL2/SDL.h>
#include "window.h"
#include "dot.h"
#include "inputHandler.h"

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

    // Create a test dot
    SDL_Color dotColor = {255, 0, 0, 255}; // Red
    Dot dot(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 20, dotColor);

    bool running = true;

    // Create input handler
    InputHandler inputHandler;

    // Set up callbacks
    inputHandler.onEscapeDown([&running]()
                              {
                                std::cout << "Escape key pressed" << std::endl;
                                running = false; });

    inputHandler.onSpaceDown([&dot]()
                             {
                                std::cout << "Space key pressed" << std::endl;
                                dot.setColor({0, 255, 0, 255}); });

    inputHandler.onLeftClick([&dot](int x, int y)
                             {
                                std::cout << "Left click at " << x << ", " << y << std::endl;
                                dot.setPosition(x, y); });

    inputHandler.onQuit([&running]()
                        {
                            std::cout << "Quit event received" << std::endl;
                            running = false; });
    Uint32 frameStart;
    int frameTime;

    // Game loop
    while (running)
    {
        frameStart = SDL_GetTicks();

        // Handle events
        inputHandler.pollEvents();

        // Update game state
        dot.update();

        // Render
        window.renderBackground(0, 0, 0); // Black background
        dot.draw(window.getRenderer());
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
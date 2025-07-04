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

    Gameplay gameplay(WINDOW_WIDTH, WINDOW_HEIGHT);

    InputHandler inputHandler;

    gameplay.setupInputCallbacks(inputHandler);
    Uint32 frameStart;
    int frameTime;

    while (gameplay.isRunning())
    {
        frameStart = SDL_GetTicks();

        inputHandler.pollEvents();

        gameplay.update();

        window.renderBackground(0, 0, 0);
        gameplay.render(window.getRenderer());
        window.present();

        gameplay.drawGrid(window.getRenderer());

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
        {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    std::cout << "Game ended successfully!" << std::endl;
    return 0;
}
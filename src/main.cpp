#include <iostream>
#include <SDL2/SDL.h>
#include "window.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main()
{
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "SDL2 Test");
    window.init();
    window.create();
    window.renderBackground();
    window.present();
    system("clear");
    std::cout << "SDL initialized successfully!" << std::endl;
    std::cout << "Press Enter to continue...";
    std::cin.get();
    SDL_Quit();
    return 0;
}
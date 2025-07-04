#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <iostream>

class Window
{
public:
    Window(int width, int height, const char *title);
    ~Window();
    int init();
    int create();
    void renderBackground();
    void renderBackground(int r, int g, int b, int a = 255);
    SDL_Renderer *getRenderer() const { return m_renderer; }
    void present();

private:
    int m_width;
    int m_height;
    const char *m_title;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
};

#endif
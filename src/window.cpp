#include <SDL2/SDL.h>
#include <iostream>
#include "window.h"

Window::Window(int width, int height, const char *title)
    : m_width(width), m_height(height), m_title(title), m_window(nullptr), m_renderer(nullptr)
{
}

Window::~Window()
{
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
    }
    if (m_window)
    {
        SDL_DestroyWindow(m_window);
    }
}

int Window::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    return 0;
}

int Window::create()
{
    m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
    if (!m_window)
    {
        std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer)
    {
        std::cout << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "SDL_CreateWindow successful!" << std::endl;
    return 0;
}

void Window::renderBackground()
{
    renderBackground(255, 255, 255, 255); // Default white background
}

void Window::renderBackground(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    SDL_RenderClear(m_renderer);
}

void Window::present()
{
    SDL_RenderPresent(m_renderer);
}
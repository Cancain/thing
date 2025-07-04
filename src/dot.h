#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>
#include <iostream>

class Dot
{
public:
    Dot(int x, int y, int radius, SDL_Color color);
    void draw(SDL_Renderer *renderer);
    void update();
    void setPosition(int x, int y);
    void setRadius(int radius);
    void setColor(SDL_Color color);

    // Getters
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getRadius() const { return m_radius; }
    SDL_Color getColor() const { return m_color; }

private:
    int m_x;
    int m_y;
    int m_radius;
    SDL_Color m_color;
    SDL_Point m_position;
};

#endif
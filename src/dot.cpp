#include "dot.h"

Dot::Dot(int x, int y, int radius, SDL_Color color)
    : m_x(x), m_y(y), m_radius(radius), m_color(color)
{
    m_position.x = x;
    m_position.y = y;
}

void Dot::draw(SDL_Renderer *renderer)
{
    for (int w = 0; w < m_radius * 2; w++)
    {
        for (int h = 0; h < m_radius * 2; h++)
        {
            int dx = m_radius - w;
            int dy = m_radius - h;
            if ((dx * dx + dy * dy) <= (m_radius * m_radius))
            {
                SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
                SDL_RenderDrawPoint(renderer, m_x + dx, m_y + dy);
            }
        }
    }
}

void Dot::update()
{
}

void Dot::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
    m_position.x = x;
    m_position.y = y;
}

void Dot::setRadius(int radius)
{
    m_radius = radius;
}

void Dot::setColor(SDL_Color color)
{
    m_color = color;
}

#include "gameplay.h"
#include <iostream>
#include <algorithm>
#include <climits>

Gameplay::Gameplay(int windowWidth, int windowHeight)
    : m_running(false), m_paused(false), m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_score(0), m_frameCount(0)
{
    initializeGame();
}

Gameplay::~Gameplay()
{
    cleanupGame();
}

void Gameplay::initializeGame()
{
    std::cout << "Initializing game..." << std::endl;

    // Add some initial dots
    addDot(m_windowWidth / 2, m_windowHeight / 2, 20, {255, 0, 0, 255}); // Red dot in center
    addDot(100, 100, 15, {0, 255, 0, 255});                              // Green dot
    addDot(m_windowWidth - 100, 100, 15, {0, 0, 255, 255});              // Blue dot

    m_running = true;
    std::cout << "Game initialized with " << m_dots.size() << " dots" << std::endl;
}

void Gameplay::cleanupGame()
{
    std::cout << "Cleaning up game..." << std::endl;
    clearDots();
    m_running = false;
}

void Gameplay::update()
{
    if (!m_running || m_paused)
    {
        return;
    }

    m_frameCount++;

    updateEntities();
    checkCollisions();
    updateGameState();
}

void Gameplay::render(SDL_Renderer *renderer)
{
    if (!m_running)
    {
        return;
    }

    // Render all dots
    for (auto &dot : m_dots)
    {
        dot->draw(renderer);
    }
}

void Gameplay::setupInputCallbacks(InputHandler &inputHandler)
{
    // Set up all input callbacks
    inputHandler.onEscapeDown([this]()
                              { onEscapePressed(); });
    inputHandler.onSpaceDown([this]()
                             { onSpacePressed(); });
    inputHandler.onLeftClick([this](int x, int y)
                             { onLeftClick(x, y); });
    inputHandler.onRightClick([this](int x, int y)
                              { onRightClick(x, y); });
    inputHandler.onQuit([this]()
                        { onQuitRequested(); });
}

void Gameplay::start()
{
    if (!m_running)
    {
        m_running = true;
        m_paused = false;
        std::cout << "Game started!" << std::endl;
    }
}

void Gameplay::pause()
{
    if (m_running && !m_paused)
    {
        m_paused = true;
        std::cout << "Game paused" << std::endl;
    }
}

void Gameplay::resume()
{
    if (m_running && m_paused)
    {
        m_paused = false;
        std::cout << "Game resumed" << std::endl;
    }
}

void Gameplay::stop()
{
    if (m_running)
    {
        m_running = false;
        std::cout << "Game stopped" << std::endl;
    }
}

void Gameplay::addDot(int x, int y, int radius, SDL_Color color)
{
    m_dots.push_back(std::make_unique<Dot>(x, y, radius, color));
    std::cout << "Added dot at (" << x << ", " << y << ") with radius " << radius << std::endl;
}

void Gameplay::removeDot(size_t index)
{
    if (index < m_dots.size())
    {
        m_dots.erase(m_dots.begin() + index);
        std::cout << "Removed dot at index " << index << std::endl;
    }
}

void Gameplay::clearDots()
{
    m_dots.clear();
    std::cout << "Cleared all dots" << std::endl;
}

void Gameplay::updateEntities()
{
    for (auto &dot : m_dots)
    {
        dot->update();
    }
}

void Gameplay::checkCollisions()
{
    // Simple collision detection between dots
    for (size_t i = 0; i < m_dots.size(); ++i)
    {
        for (size_t j = i + 1; j < m_dots.size(); ++j)
        {
            // Calculate distance between dot centers
            int dx = m_dots[i]->getX() - m_dots[j]->getX();
            int dy = m_dots[i]->getY() - m_dots[j]->getY();
            int distanceSquared = dx * dx + dy * dy;

            int radiusSum = m_dots[i]->getRadius() + m_dots[j]->getRadius();
            int radiusSumSquared = radiusSum * radiusSum;

            if (distanceSquared <= radiusSumSquared)
            {
                // Collision detected!
                std::cout << "Collision detected between dots " << i << " and " << j << std::endl;
                m_score += 10;
            }
        }
    }
}

void Gameplay::updateGameState()
{
    // Update game statistics
    if (m_frameCount % 60 == 0)
    { // Every second at 60 FPS
        std::cout << "Score: " << m_score << ", Dots: " << m_dots.size() << std::endl;
    }
}

void Gameplay::onEscapePressed()
{
    std::cout << "Escape pressed - stopping game" << std::endl;
    stop();
}

void Gameplay::onSpacePressed()
{
    std::cout << "Space pressed - toggling pause" << std::endl;
    if (m_paused)
    {
        resume();
    }
    else
    {
        pause();
    }
}

void Gameplay::onLeftClick(int x, int y)
{
    std::cout << "Left click at (" << x << ", " << y << ") - adding dot" << std::endl;
    SDL_Color randomColor = {
        static_cast<Uint8>(rand() % 256),
        static_cast<Uint8>(rand() % 256),
        static_cast<Uint8>(rand() % 256),
        255};
    addDot(x, y, 10 + (rand() % 20), randomColor);
}

void Gameplay::onRightClick(int x, int y)
{
    std::cout << "Right click at (" << x << ", " << y << ") - removing nearest dot" << std::endl;
    if (!m_dots.empty())
    {
        // Find the dot closest to the click
        size_t nearestIndex = 0;
        int minDistance = INT_MAX;

        for (size_t i = 0; i < m_dots.size(); ++i)
        {
            int dx = m_dots[i]->getX() - x;
            int dy = m_dots[i]->getY() - y;
            int distance = dx * dx + dy * dy;

            if (distance < minDistance)
            {
                minDistance = distance;
                nearestIndex = i;
            }
        }

        removeDot(nearestIndex);
    }
}

void Gameplay::onQuitRequested()
{
    std::cout << "Quit requested - stopping game" << std::endl;
    stop();
}

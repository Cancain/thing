#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "inputHandler.h"
#include "dot.h"

class Gameplay
{
public:
    Gameplay(int windowWidth, int windowHeight);
    ~Gameplay();

    // Main game loop methods
    void update();
    void render(SDL_Renderer *renderer);
    bool isRunning() const { return m_running; }

    // Input handling
    void setupInputCallbacks(InputHandler &inputHandler);

    // Game state management
    void start();
    void pause();
    void resume();
    void stop();

    // Entity management
    void addDot(int x, int y, int radius, SDL_Color color);
    void removeDot(size_t index);
    void clearDots();
    size_t getDotCount() const { return m_dots.size(); }

    // Game logic
    void updateEntities();
    void checkCollisions();
    void updateGameState();

private:
    // Game state
    bool m_running;
    bool m_paused;
    int m_windowWidth;
    int m_windowHeight;

    // Entities
    std::vector<std::unique_ptr<Dot>> m_dots;

    // Game statistics
    int m_score;
    int m_frameCount;

    // Input callbacks
    void onEscapePressed();
    void onSpacePressed();
    void onLeftClick(int x, int y);
    void onRightClick(int x, int y);
    void onQuitRequested();

    // Helper methods
    void initializeGame();
    void cleanupGame();
};

#endif
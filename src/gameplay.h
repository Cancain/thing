#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "inputHandler.h"
#include "dot.h"
#include "grid.h"

class Gameplay
{
public:
    Gameplay(int windowWidth, int windowHeight);
    ~Gameplay();

    void update();
    void render(SDL_Renderer *renderer);
    bool isRunning() const { return m_running; }

    void setupInputCallbacks(InputHandler &inputHandler);

    void start();
    void pause();
    void resume();
    void stop();

    void addDot(int x, int y, int radius, SDL_Color color);
    void removeDot(size_t index);
    void clearDots();
    size_t getDotCount() const { return m_dots.size(); }

    void drawGrid(SDL_Renderer *renderer);
    void addDotToGrid(int row, int col, int radius, SDL_Color color);
    void removeDotFromGrid(int row, int col);
    void clearGrid();
    Grid *getGrid() { return m_grid.get(); }

    void updateEntities();
    void checkCollisions();
    void updateGameState();

private:
    bool m_running;
    bool m_paused;
    int m_windowWidth;
    int m_windowHeight;

    std::vector<std::unique_ptr<Dot>> m_dots;

    std::unique_ptr<Grid> m_grid;

    int m_score;
    int m_frameCount;

    void onEscapePressed();
    void onSpacePressed();
    void onLeftClick(int x, int y);
    void onRightClick(int x, int y);
    void onQuitRequested();

    void initializeGame();
    void cleanupGame();
};

#endif
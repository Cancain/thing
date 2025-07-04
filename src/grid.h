#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "dot.h"

class Grid
{
public:
    Grid(int windowWidth, int windowHeight);
    ~Grid();

    static const int GRID_SIZE = 4;

    void draw(SDL_Renderer *renderer);
    void update();

    void setCell(int row, int col, std::unique_ptr<Dot> dot);
    Dot *getCell(int row, int col) const;
    void clearCell(int row, int col);
    void clearAllCells();

    int getCellSize() const { return m_cellSize; }
    int getCellX(int col) const;
    int getCellY(int row) const;
    bool isValidCell(int row, int col) const;

    bool getCellFromPosition(int screenX, int screenY, int &row, int &col) const;

    void drawGridLines(SDL_Renderer *renderer);
    void setGridLineColor(SDL_Color color) { m_gridLineColor = color; }
    void setGridLineThickness(int thickness) { m_gridLineThickness = thickness; }

private:
    int m_windowWidth;
    int m_windowHeight;
    int m_cellSize;
    int m_gridLineThickness;
    SDL_Color m_gridLineColor;

    std::vector<std::vector<std::unique_ptr<Dot>>> m_grid;

    void calculateCellSize();
    void initializeGrid();
};

#endif
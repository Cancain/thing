#include "grid.h"
#include <iostream>

Grid::Grid(int windowWidth, int windowHeight)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_cellSize(0), m_gridLineThickness(2), m_gridLineColor({100, 100, 100, 255})
{
    calculateCellSize();
    initializeGrid();

    std::cout << "Grid created: " << GRID_SIZE << "x" << GRID_SIZE
              << " with cell size " << m_cellSize << "x" << m_cellSize << std::endl;
}

Grid::~Grid()
{
    clearAllCells();
}

void Grid::calculateCellSize()
{
    int totalGridLineThickness = (GRID_SIZE + 1) * m_gridLineThickness;

    int availableWidth = m_windowWidth - totalGridLineThickness;
    int availableHeight = m_windowHeight - totalGridLineThickness;

    m_cellSize = std::min(availableWidth / GRID_SIZE, availableHeight / GRID_SIZE);

    std::cout << "Calculated cell size: " << m_cellSize << std::endl;
}

void Grid::initializeGrid()
{
    m_grid.resize(GRID_SIZE);
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        m_grid[i].resize(GRID_SIZE);
    }
}

void Grid::draw(SDL_Renderer *renderer)
{
    drawGridLines(renderer);

    for (int row = 0; row < GRID_SIZE; ++row)
    {
        for (int col = 0; col < GRID_SIZE; ++col)
        {
            if (m_grid[row][col])
            {
                m_grid[row][col]->draw(renderer);
            }
        }
    }
}

void Grid::update()
{
    for (int row = 0; row < GRID_SIZE; ++row)
    {
        for (int col = 0; col < GRID_SIZE; ++col)
        {
            if (m_grid[row][col])
            {
                m_grid[row][col]->update();
            }
        }
    }
}

void Grid::setCell(int row, int col, std::unique_ptr<Dot> dot)
{
    if (!isValidCell(row, col))
    {
        std::cout << "Invalid cell position: (" << row << ", " << col << ")" << std::endl;
        return;
    }

    int cellX = getCellX(col);
    int cellY = getCellY(row);

    if (dot)
    {
        dot->setPosition(cellX + m_cellSize / 2, cellY + m_cellSize / 2);
    }

    m_grid[row][col] = std::move(dot);
    std::cout << "Set cell (" << row << ", " << col << ") with dot" << std::endl;
}

Dot *Grid::getCell(int row, int col) const
{
    if (!isValidCell(row, col))
    {
        return nullptr;
    }
    return m_grid[row][col].get();
}

void Grid::clearCell(int row, int col)
{
    if (!isValidCell(row, col))
    {
        return;
    }

    m_grid[row][col].reset();
    std::cout << "Cleared cell (" << row << ", " << col << ")" << std::endl;
}

void Grid::clearAllCells()
{
    for (int row = 0; row < GRID_SIZE; ++row)
    {
        for (int col = 0; col < GRID_SIZE; ++col)
        {
            m_grid[row][col].reset();
        }
    }
    std::cout << "Cleared all grid cells" << std::endl;
}

int Grid::getCellX(int col) const
{
    if (col < 0 || col >= GRID_SIZE)
    {
        return -1;
    }
    return col * (m_cellSize + m_gridLineThickness) + m_gridLineThickness;
}

int Grid::getCellY(int row) const
{
    if (row < 0 || row >= GRID_SIZE)
    {
        return -1;
    }
    return row * (m_cellSize + m_gridLineThickness) + m_gridLineThickness;
}

bool Grid::isValidCell(int row, int col) const
{
    return row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE;
}

bool Grid::getCellFromPosition(int screenX, int screenY, int &row, int &col) const
{
    for (int r = 0; r < GRID_SIZE; ++r)
    {
        for (int c = 0; c < GRID_SIZE; ++c)
        {
            int cellX = getCellX(c);
            int cellY = getCellY(r);

            if (screenX >= cellX && screenX < cellX + m_cellSize &&
                screenY >= cellY && screenY < cellY + m_cellSize)
            {
                row = r;
                col = c;
                return true;
            }
        }
    }
    return false;
}

void Grid::drawGridLines(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer,
                           m_gridLineColor.r,
                           m_gridLineColor.g,
                           m_gridLineColor.b,
                           m_gridLineColor.a);

    for (int col = 0; col <= GRID_SIZE; ++col)
    {
        int x = col * (m_cellSize + m_gridLineThickness) + m_gridLineThickness / 2;
        SDL_RenderDrawLine(renderer, x, 0, x, m_windowHeight);
    }

    for (int row = 0; row <= GRID_SIZE; ++row)
    {
        int y = row * (m_cellSize + m_gridLineThickness) + m_gridLineThickness / 2;
        SDL_RenderDrawLine(renderer, 0, y, m_windowWidth, y);
    }
}

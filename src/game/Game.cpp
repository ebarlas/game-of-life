#include "Game.h"

using namespace gameoflife;

Game::Game(BitMatrix grid, const Dimension &dim, SDL_Renderer *ren) : grid{std::move(grid)}, dim{dim}, ren{ren} {

}

int Game::countNeighbors(int row, int col) {
    int count = 0;
    for (int r = row - 1; r <= row + 1; r++) {
        for (int c = col - 1; c <= col + 1; c++) {
            if (r >= 0 && r < grid.getRows() && c >= 0 && c < grid.getColumns()) {
                if (r != row || c != col) {
                    if (grid.get(r, c)) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

bool Game::aliveInNextGen(int row, int col) {
    int count = countNeighbors(row, col);
    bool alive = grid.get(row, col);
    return (alive && (count == 2 || count == 3)) || (!alive && count == 3);
}

void Game::update() {
    BitMatrix next{grid.getRows(), grid.getColumns()};
    for (int r = 0; r < grid.getRows(); r++) {
        for (int c = 0; c < grid.getColumns(); c++) {
            if (aliveInNextGen(r, c)) {
                next.set(r, c);
            }
        }
    }
    grid = std::move(next);
}

void Game::render() {
    SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
    auto screen = SDL_Rect{0, 0, dim.getWidth(), dim.getHeight()};
    SDL_RenderFillRect(ren, &screen);

    int grey = 200;
    SDL_SetRenderDrawColor(ren, grey, grey, grey, SDL_ALPHA_OPAQUE);

    int rowHeight = dim.getHeight() / grid.getRows();
    for (int i = 0; i <= grid.getRows(); i++) {
        SDL_RenderDrawLine(ren, 0, i * rowHeight, dim.getWidth(), i * rowHeight);
    }

    int colWidth = dim.getWidth() / grid.getColumns();
    for (int i = 0; i <= grid.getColumns(); i++) {
        SDL_RenderDrawLine(ren, i * colWidth, 0, i * colWidth, dim.getHeight());
    }

    SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
    int tileWidth = dim.getWidth() / grid.getColumns();
    int tileHeight = dim.getHeight() / grid.getRows();

    for (int r = 0; r < grid.getRows(); r++) {
        for (int c = 0; c < grid.getColumns(); c++) {
            if (grid.get(r, c)) {
                auto tile = SDL_Rect{c * tileWidth, r * tileHeight, tileWidth, tileHeight};
                SDL_RenderFillRect(ren, &tile);
            }
        }
    }
}

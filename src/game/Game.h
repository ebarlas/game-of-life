#ifndef GAMEOFLIFE_GAME_H
#define GAMEOFLIFE_GAME_H

#include "SDL.h"
#include "../util/BitMatrix.h"
#include "../util/Dimension.h"

namespace gameoflife {
    class Game {
    public:
        Game(BitMatrix grid, const Dimension &dim, SDL_Renderer *ren);
        void update();
        void render();
    private:
        BitMatrix grid;
        const Dimension &dim;
        SDL_Renderer *ren;
        int countNeighbors(int row, int col);
        bool aliveInNextGen(int row, int col);
    };
}

#endif

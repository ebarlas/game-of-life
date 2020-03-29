#include <iostream>
#include <fstream>
#include "util/FpsLogger.h"
#include "util/BitMatrix.h"
#include "game/Game.h"
#include "SDL.h"

using namespace std;
using namespace gameoflife;

int main(int argc, const char **argv) {
    if (argc != 3) {
        cout << "2 arguments required: [grid file] [frames per update]" << endl;
        return 1;
    }

    Dimension dim{800, 600};

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Game of Life", 100, 100, dim.getWidth(), dim.getHeight(), SDL_WINDOW_SHOWN);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    FpsLogger fpsLogger{std::cout};

    int cellSide = 20;
    int rows = dim.getHeight() / cellSide;
    int columns = dim.getWidth() / cellSide;
    BitMatrix grid{rows, columns};

    std::ifstream fs{argv[1]};
    fs >> grid;

    Game game(grid, dim, ren);
    game.render();
    SDL_RenderPresent(ren);

    int frames = 0;
    int framesPerUpdate = std::stoi(argv[2]);

    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        if (++frames % framesPerUpdate == 0)
            game.update();
        game.render();

        SDL_RenderPresent(ren);

        fpsLogger.increment();
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

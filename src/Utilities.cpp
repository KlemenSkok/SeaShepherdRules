
// Utilities.cpp

#include "Utilities.hpp"
#include "Constants.hpp"

#include <SDL2/SDL_render.h>
#include <cmath>


namespace Window {

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    void Create() {
        window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //white
    }

    void Maximize() {
        SDL_MaximizeWindow(window);
    }

    void Fullscreen() {
/*         SDL_Rect window_data;
        SDL_GetDisplayBounds(SDL_GetWindowDisplayIndex(window), &window_data);
        SDL_SetWindowSize(window, window_data.w, window_data.h); */
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }

    void Destroy() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }

}

void update_movement(SDL_Rect &rect, int dest_x, int dest_y, int speed) {
    int dx = dest_x - rect.x;
    int dy = dest_y - rect.y;
    int hypotenuse = std::sqrt(dx * dx + dy * dy);

    if(hypotenuse != 0) {
        dx = dx * speed / hypotenuse;
        dy = dy * speed / hypotenuse;
    }

    rect.x += dx;
    rect.y += dy;
}
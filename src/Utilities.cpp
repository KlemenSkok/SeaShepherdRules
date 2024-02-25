
// Utilities.cpp

#include "Utilities.hpp"
#include "Constants.hpp"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
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
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }

    void Destroy() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }

    int Width() {
        int w;
        SDL_GetWindowSize(window, &w, nullptr);
        return w;
    }

    int Height() {
        int h;
        SDL_GetWindowSize(window, nullptr, &h);
        return h;
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

SDL_Texture* LoadTexture(const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}


struct testStruct {
    int a;
};
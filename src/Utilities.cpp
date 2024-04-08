
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

void update_movement(SDL_Rect &rect, int dest_x, int dest_y, double input_speed) {
    int distance_x = dest_x - rect.x;
    int distance_y = dest_y - rect.y;

    double angle = atan2(distance_y, distance_x) * 180.0 / M_PI;

    double speed = input_speed;
    double speed_x = speed * cos(angle * M_PI / 180.0);
    double speed_y = speed * sin(angle * M_PI / 180.0);

    //std::cout << "speed_x: " << speed_x << "\nspeed_y: " << speed_y << std::endl;
    
    if(std::abs(distance_x) <= std::abs(speed_x) && std::abs(distance_y) <= std::abs(speed_y)) {
        // da ostane pr mir k pride na cilj
        rect.x = dest_x;
        rect.y = dest_y;
    }
    else {
        rect.x += static_cast<int>(floor(speed_x));
        rect.y += static_cast<int>(floor(speed_y));
    }
}


SDL_Texture* LoadTexture(const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void format_path(char *path) { //replace \\ with /
    int i = 0;
    while(*(path + i) != '\0') {
        if(*(path + i) == '\\')
            *(path + i) = '/';
    }
}



SDL_Texture *RenderText(const char *text, TTF_Font *font, SDL_Color color) {
    
    SDL_Surface *s = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *t = SDL_CreateTextureFromSurface(Window::renderer, s);
    SDL_FreeSurface(s);

    return t;
}
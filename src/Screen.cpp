
// Screen.cpp

#include "Screen.hpp"
#include "Utilities.hpp"

#include <SDL2/SDL.h>


Screen::Screen() {
    texture = nullptr;
    container = {0, 0, 0, 0};
}

Screen::~Screen() {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Screen::main_menu() {
    texture = LoadTexture("../../assets/images/menus/main_menu.png");
    bool exit = false;

    while(!exit) {
        container = {0, 0, Window::Width(), Window::Height()};
        SDL_RenderClear(Window::renderer);
        SDL_RenderCopy(Window::renderer, texture, NULL, &container);
        SDL_RenderPresent(Window::renderer);
    }
}

void Screen::pause_menu() {
    texture = LoadTexture("../../assets/images/menus/pause_menu.png");
    bool exit = false;

}

void Screen::defeat_screen() {
    texture = LoadTexture("../../assets/images/menus/defeat_screen.png");
    bool exit = false;

}

void Screen::victory_screen() {
    texture = LoadTexture("../../assets/images/menus/victory_screen.png");
    bool exit = false;

}

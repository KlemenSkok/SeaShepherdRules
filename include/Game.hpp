#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
//#include "Player.hpp"
//#include "Enemy.hpp"
//#include "WindowManager.hpp"
//#include "Constants.hpp"


class Game {

    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    Game();
    ~Game();

    void init();
    void run();
    void cleanup();
};
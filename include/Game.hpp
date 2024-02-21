
// Game.hpp

#pragma once

#include "ResourceManager.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <vector>
//#include "Player.hpp"
//#include "Enemy.hpp"
//#include "WindowManager.hpp"
//#include "Constants.hpp"


class Game {

    static bool _isRunning;
    static int _currentLevel;

    SDL_Texture *testTexture;

    ResourceManager resourceManager();


public:

    static SDL_Window *_window;
    static SDL_Renderer *_renderer;

    Game();
    ~Game();

    void init();
    void run();
    void cleanup();
};
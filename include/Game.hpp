
// Game.hpp

#pragma once

#include "ResourceManager.hpp"
#include "Utilities.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Constants.hpp"
#include "Level.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <vector>
#include <iostream>


using namespace Window;


class Game {

    static bool _isRunning;
    static int _currentLevel;

    ResourceManager resourceManager();

    void setScreen(int mode);
    void gameScreen(int level);


public:

    Game();
    ~Game();

    void init();
    int run(int level);
    void cleanup();
};
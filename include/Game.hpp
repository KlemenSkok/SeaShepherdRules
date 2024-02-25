
// Game.hpp

#pragma once

#include "ResourceManager.hpp"
#include "Utilities.hpp"
#include "Enemy.hpp"
//#include "Player.hpp"
//#include "Constants.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <vector>

using namespace Window;


class Game {

    static bool _isRunning;
    static int _currentLevel;

    std::vector<Enemy*> enemies;

    ResourceManager resourceManager();

    void setScreen(int mode);
    void gameScreen(int level);


public:

    Game();
    ~Game();

    void init();
    void run();
    void cleanup();
};
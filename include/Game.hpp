
// Game.hpp

#pragma once

#include "Utilities.hpp"
#include "Pirate.hpp"
#include "Player.hpp"
#include "Constants.hpp"
#include "Level.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>


using namespace Window;


class Game {

    static bool _isRunning;
    static int _currentLevel;
    static int _gameState;


    void setScreen(int mode);
    void gameScreen(int level);


public:

    Game();
    ~Game();

    void init();
    int run(int level);
    void cleanup();
};
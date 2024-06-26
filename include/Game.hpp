
// Game.hpp

#pragma once

#include "Utilities.hpp"
#include "Pirate.hpp"
#include "Player.hpp"
#include "Constants.hpp"
#include "Level.hpp"
#include "Hint.hpp"
#include "Screen.hpp"
#include "Replay.hpp"
#include "Leaderboard.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>
#include <chrono>


using namespace Window;


class Game {

    static bool _isRunning;
    static int _currentLevel;
    static int _gameState;

    Screen screen;


public:

    Game();
    ~Game();

    void init();
    int run(int level);
    void cleanup();
};
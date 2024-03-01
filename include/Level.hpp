
// Level.hpp

#pragma once

#include "Player.hpp"
#include "Enemy.hpp"
#include "Vektor.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"

#include <SDL2/SDL_image.h>

using namespace Window;


class Level {

    SDL_Texture *background;

    Player player;
    
    Vektor<Whaler*> whalers;
    int numWhalers;

public:
    Level(int levelNum);
    ~Level();

    void Update();
    void Render();
    void Cleanup();
};
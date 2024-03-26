
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
    Vektor<Iceberg*> icebergs;
    Vektor<Atol*> atols;
    int initialWhalerCount;

    void checkCollisions();

public:
    Level(int levelNum);
    ~Level();

    int Update();
    void Render();
    void Cleanup();

    SDL_Rect get_hitbox();
};

// Level.hpp

#pragma once

#include "Player.hpp"
#include "Pirate.hpp"
#include "Vektor.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"
#include "Hint.hpp"
#include "Healthbar.hpp"

#include <SDL2/SDL_image.h>

using namespace Window;


class Level {

    SDL_Texture *background;

    Player player;
    
    Vektor<Whaler*> whalers;
    Vektor<Iceberg*> icebergs;
    Vektor<Atol*> atols;
    Vektor<Pirate*> pirates;
    int initialWhalerCount;

    Hint hint;
    Healthbar healthbar;

    Uint64 ms_LastHint;
    Uint64 ms_tillNestHint;


    void checkCollisions();

public:
    Level(int levelNum);
    ~Level();

    int Update();
    void Render();
    void Cleanup();

    Vektor<struct ReplayObject>* dumpFrame();

    SDL_Rect get_hitbox();
};
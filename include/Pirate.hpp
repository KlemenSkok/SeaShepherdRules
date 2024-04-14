
// Enemy.hpp

#pragma once

#include "Entity.hpp"

#include <SDL2/SDL_image.h>

/*
About:
    - Level 3
    - igralca napadajo (v določenem radiju) in mu odvzamejo HP
        -> pridejo zelo hitro, se pipnejo igralca in zbežijo
        -> igralec jih ne more uničt
    - ko igralec ni v dosegu -> random movement / išče igralca
*/

class Pirate : public Entity {

    static int ID_counter;

    int dest_x, dest_y;
    int prev_x, prev_y;
    Uint64 ms_toWait;
    Uint64 ms_atLastStop;
    Uint64 ms_atLastAttack;
    
    bool is_stopped;
    bool attack_player;
    bool get_away;

public:
    int object_ID;

    Pirate();
    ~Pirate();

    void Initialize() override;
    void CheckCollisions() override;
    void CheckBorders() override;
    void Update() override;
    void Render() override;

    void generate_dest_coords();
    void CheckPlayerDistance(SDL_Rect);

    SDL_Rect get_hitbox();
    struct ReplayObject dumpObject();

    //...
};

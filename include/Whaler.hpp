
// Whaler.hpp

// (kitolovci)

#pragma once

#include "Entity.hpp"

#include <SDL2/SDL_image.h>

/*
About:
    - Cilj igre je, da igralec lovi kitolovce.
    - premikajo se po polju, igralcu niso vidni izven določenega radija
    - sami se ne morejo braniti
    - če sta dva dovolj blizu, se lahko postavita skupaj
    - takrat lahko poškodujeta igralca
*/

class Whaler : public Entity {

    static int ID_counter;
    //int health;

    int dest_x, dest_y;
    Uint64 ms_toWait;
    Uint64 ms_atLastStop;
    bool is_stopped;
    bool is_chased;

    void generate_dest_coords();

public:
    int object_ID;

    Whaler();
    ~Whaler();

    void Initialize() override;
    void CheckCollisions() override;
    void CheckBorders() override;
    void Update() override;
    void Render() override;

    void CheckPlayerDistance(SDL_Rect);

    SDL_Rect get_hitbox();
};

//#include "Vektor.hpp"

//template class Vektor<Whaler*>;
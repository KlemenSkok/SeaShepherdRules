
// Iceberg.hpp

#pragma once

#include "Entity.hpp"
#include "Utilities.hpp"
#include "Constants.hpp"
#include "Logger.hpp"

#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <cmath>

/*
About:
    - Level 1
    - počas (zlo počas) se premikajo po ekranu. 
    - So ovira za igralca in kitolovce. 
    - ko grejo iz polja se uničijo. 
    - random položaj, smer, velikost. (hitrost?)

    - aja, pa čez njih naj ne bi vidu ostalih entityjev!?
*/

class Iceberg : public Entity {

    static int ID_counter;
    static double direction; // angle 0-360 deg

    Uint32 ticksCounter;

public:
    int object_ID;

    Iceberg();
    ~Iceberg();

    void Initialize() override;
    void CheckCollisions() override;
    void CheckBorders() override;
    void Update() override;
    void Render() override;

    SDL_Rect get_hitbox();
};

// Iceberg.hpp

#pragma once

#include "Entity.hpp"

#include <SDL2/SDL_image.h>

/*
About:
    - Level 1
    - počas (zlo počas) se premikajo po ekranu. 
    - So ovira za igralca in kitolovce. 
    - ko grejo iz polja se uničijo. 
    - random položaj, smer, velikost. (hitrost?)
*/

class Iceberg : public Entity {

    static int ID_counter;

public:
    int object_ID;

    Iceberg();
    ~Iceberg();

    void Initialize() override;
    void CheckCollisions() override;
    void CheckBorders() override;
    void Update() override;
    void Render() override;
}
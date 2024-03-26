
// Atol.hpp

#pragma once

#include "Entity.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"
#include "Logger.hpp"

#include <SDL2/SDL_Image.h>
#include <cstdlib>
#include <cmath>
#include <ctime>

/*
About:
    - Level 2
    - so fiksirani na svoj začetni položaj. 
    - so ovira za igralca in kitolovce.
    - počasi rastejo (pri določeni velikosti izginejo?)
*/


class Atol : public Entity {

    static int ID_counter;

    Uint32 ticksCounter;
    Uint32 waitTimer;
    bool isVanishing;
    Uint8 textureOpacity;
    bool timeout;

public:
    int object_ID;

    Atol();
    ~Atol();

    void Initialize() override;
    void CheckCollisions() override;
    void CheckBorders() override;
    void Update() override;
    void Render() override;

    static void setSize(int);
    bool operator==(const SDL_Rect&) const;

    SDL_Rect get_hitbox();
};
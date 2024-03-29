
// Enemy.hpp

#pragma once

#include "Entity.hpp"

#include <SDL2/SDL_image.h>

/*
About:
    - Level 3
    - TODO: preimenuj v Pirate
    - igralca napadajo (v določenem radiju) in mu odvzamejo HP
    - ko igralec ni v dosegu -> random movement / išče igralca
    - igralec jih lahko uniči (kako?)
*/

class Enemy : public Entity {

    static int ID_counter;

public:
    int object_ID;

    Enemy();
    ~Enemy();

    void Initialize() override;
    void CheckCollisions() override;
    void CheckBorders() override;
    void Update() override;
    void Render() override;


    //...
};

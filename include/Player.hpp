 
// Player.hpp

//igralec

#pragma once

#include "Entity.hpp"

//#include <SDL2/SDL_image.h>

/*
About:
    - igralec lovi kitolovce
    - ubije jih tako, da se jih dotakne
    - če bo cajt -> orožje na delč??
*/

class Player : public Entity {


public:
    Player();
    ~Player();

    void Initialize() override;
    void CheckCollisions() override;
    void CheckBorders() override; // TO-DO
    void Update() override;
    void Render() override;

    void UpdateMouseMovement(); // TO-DO
    bool operator==(const SDL_Rect);

    //...
};
 
// Player.hpp

//igralec

#pragma once

#include "Entity.hpp"

//#include <SDL2/SDL_image.h>

class Player : public Entity {


public:
    Player(SDL_Texture *texture);
    ~Player();

    void CheckCollisions() override;
    void Update() override;
    void UpdateMouseMovement();
    void Render() override;

    //...
};
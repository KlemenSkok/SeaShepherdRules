 
// Player.hpp

//igralec

#pragma once

#include "Entity.hpp"

//#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

class Player : public Entity {


public:
    Player();
    ~Player();

    void CheckCollisions() override;
    void Update() override;
    void Render(SDL_Texture *texture) override;

    //...
};
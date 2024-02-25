
// Entity.hpp

#pragma once

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

class Entity {

protected:
    SDL_Rect container, // tuki not gre slika/textura
             hitbox; // mal manjsi kt container
    SDL_Texture *texture;

public:

    virtual void Initialize() = 0;
    virtual void CheckCollisions() = 0;
    virtual void CheckBorders() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    //...
};

// Entity.hpp

#pragma once

#include <SDL2/SDL_Rect.h>
#include <SDL2/SDL_render.h>

class Entity {

protected:
    SDL_Rect box;

public:
    Entity(); // Load Texture,...
    ~Entity(); // Free Texture,...

    virtual void CheckCollisions() = 0;
    virtual void Update() = 0;
    virtual void Render(SDL_Texture *texture) = 0;
    //...
};
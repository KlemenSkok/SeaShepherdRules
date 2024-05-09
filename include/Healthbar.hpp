
// Healthbar.hpp

#pragma once
#include <SDL2/SDL.h>



class Healthbar {

    SDL_Rect inner, outer;
    SDL_Color color;

public:
    
    Healthbar();

    void Update(Uint8);
    void Render();


};

// Hint.hpp

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>


// TO-DO: narisat pravokotnik okoli teksta, da izstopa

class Hint {

    SDL_Texture *texture;
    TTF_Font *font;
    SDL_Rect container;
    std::string text;

    // 10s == ~600 ticks
    Uint32 ms_toWait;
    bool hintActive;

public:
    
    Hint();
    ~Hint();

    void Refresh(SDL_Rect);
    void Render();
    void Empty();

    bool toRefresh;

};
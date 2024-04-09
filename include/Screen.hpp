
// Screen.hpp

#pragma once

#include <SDL2/SDL_image.h>

/*
About:
    - class, ki narise zazlicne menije
        -> main menu, 
        -> pause menu, 
        -> defeat screen, 
        -> victory screen

*/

class Screen {

    SDL_Texture *texture;
    SDL_Rect container;


public:

    Screen();
    ~Screen();

    void main_menu();
    void pause_menu();
    void defeat_screen();
    void victory_screen();

};
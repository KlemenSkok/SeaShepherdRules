
// Utilities.hpp

#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Commonly used functions and structures

void update_movement(SDL_Rect &rect, int dest_x, int dest_y, double speed);

SDL_Texture *LoadTexture(const char *path);
void LoadWhaler(SDL_Texture *&, int); 
SDL_Texture *RenderText(const char *text, TTF_Font *font, SDL_Color color);


void format_path(char *path);


namespace Window {
        extern SDL_Window *window;
        extern SDL_Renderer *renderer;

        void Create();
        void Destroy();

        void Maximize();
        void Fullscreen();

        int Width();
        int Height();
} 

/*
? extern <variable>
*   The extern keyword, when used in a variable declaration, 
*   tells the compiler that the variable is declared but not defined in the current translation unit. 
*   Instead, the variable is defined elsewhere (usually in another translation unit), 
*   and the linker will resolve the actual definition during the linking phase.
*/


/**
 * @brief
 * 
 * Te strukture se bojo zapisvale v bin datoteko za replay.
 * 
 * @param type Tip strukture. lahko je igralec, kitolovec, itd.
 *      Vec opisa v Constants.hpp
 * @param container SDL_Rect, ki predstavlja polozaj in velikost objekta.
*/
struct ReplayObject {
        char type;
        uint8_t level;
        SDL_Rect container;
};